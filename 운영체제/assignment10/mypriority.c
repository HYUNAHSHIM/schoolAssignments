#include "sched.h"

void init_myprio_rq(struct myprio_rq *myprio_rq)
{
	printk(KERN_INFO"***[MYPRIO] MYPRIO class is online\n");
	myprio_rq->nr_running=0;
	INIT_LIST_HEAD(&myprio_rq->queue);
}
void init_task_myprio(struct task_struct *p)
{
	//init task
	struct sched_myprio_entity *entity = &p->myprio;
	p->sched_class = &myprio_sched_class;
	if((entity->stride % 100) < 50)
		entity->aging = (entity->stride)/100;
	else	
		entity->aging = (entity->stride)/100 + 1;
	//every task will be excuted before 100 updates
	entity->pass = entity->stride;
	printk(KERN_INFO"***[MYPRIO] initialize task: stride=%d, aging=%d, pass=%d\n", entity->stride, entity->aging, entity->pass);
}
static void update_curr_myprio(struct rq *rq)
{
	struct sched_myprio_entity *entity = NULL;
	struct myprio_rq *myprio_rq = &rq->myprio;
	struct task_struct *p = NULL;
	struct list_head *myprio_q = &myprio_rq->queue;
	
	printk(KERN_INFO"\t***[MYPRIO] update_curr start\n");
	//add stride to pass of task which is currently executing. This makes this task's priority decrease.(aging)
	((rq->curr)->myprio).pass += ((rq->curr)->myprio).stride;
	int i;
	//For task which is not executing, subtract stride from pass. This makes this task's priority increase.(aging)
	for(i=0;i<myprio_rq->nr_running;i++){
		myprio_q = myprio_q->next;
		entity = container_of(myprio_q, struct sched_myprio_entity, run_list);
		p = container_of(entity, struct task_struct, myprio);
		//if task is not executing one
		if((rq->curr)->pid != p->pid){
			if((entity->pass - entity->aging) < 0)
				entity->pass = 0;
			//By decreasing other tasks pass which is not executing now, it's priority increases
			entity->pass -= entity->aging;
		}
		printk(KERN_INFO"\t\t***[MYPRIO] update_curr: curr->pid=%d, p->pid=%d, pass=%d, stride=%d\n", (rq->curr)->pid, p->pid, entity->pass, entity->stride);
	}
	//reschedule
	resched_curr(rq);
	printk(KERN_INFO"\t***[MYPRIO] update_curr: update_curr end\n");

}

static void enqueue_task_myprio(struct rq *rq, struct task_struct *p, int flags) 
{
	struct myprio_rq *myprio_rq = &rq->myprio;
	struct sched_myprio_entity *mse = &p->myprio;
	struct list_head *myprio_queue = &myprio_rq->queue;
	struct list_head *mse_run_list = &mse->run_list;
	
	//enqueue to last order
	list_add_tail(mse_run_list, myprio_queue);
	//increase nr_running nad change state
	myprio_rq->nr_running++;
	printk(KERN_INFO"***[MYPRIO] enqueue: success cpu=%d, nr_running=%d, p->state=%lu, p->pid=%d, pass=%u, stride=%u\n",cpu_of(rq), myprio_rq->nr_running,p->state,p->pid,mse->pass, mse->stride);
}
static void dequeue_task_myprio(struct rq *rq, struct task_struct *p, int flags) 
{
	struct myprio_rq *myprio_rq = &rq->myprio;
	struct sched_myprio_entity *mse = &p->myprio;
	struct list_head *myprio_queue = &myprio_rq->queue;
	struct list_head *mse_run_list = &mse->run_list;
	
	//check whether queue is empty
	if(myprio_rq->nr_running != 0)
	{
		//delete the task and decrease nr_running
		list_del_init(mse_run_list);
		myprio_rq->nr_running--;
		printk(KERN_INFO"***[MYPRIO] dequeue: success cpu=%d, nr_running=%d, p->state=%lu, p->pid=%d, pass=%u, stride=%u\n",cpu_of(rq), myprio_rq->nr_running,p->state, p->pid, mse->pass, mse->stride);
	}
	else{
	}
	
}
void check_preempt_curr_myprio(struct rq *rq, struct task_struct *p, int flags) {
	printk(KERN_INFO"***[MYPRIO] check_preempt_curr_myprio\n");
}
struct task_struct *pick_next_task_myprio(struct rq *rq, struct task_struct *prev)
{
	struct myprio_rq *myprio_rq = &rq->myprio;
	struct list_head *myprio_queue = &myprio_rq->queue;
	struct sched_myprio_entity *entity = NULL;
	struct task_struct *next_p = NULL;
	struct sched_myprio_entity *next_entity = NULL;
	
	//if there's no running one
	if(myprio_rq->nr_running == 0)
		return NULL;
	
	if(prev->sched_class != &myprio_sched_class){
		printk(KERN_INFO"***[MYPRIO] pick_next_task: prev->pid=%d\n", prev->pid);
		put_prev_task(rq, prev);
	}
	//select the task in rq which has minimum pass value
	//if the minimum one is more than 2, select the minimum stride.
	int i;
	unsigned int pass_min;
	unsigned int stride_min;
	
	next_entity = container_of(myprio_queue->next, struct sched_myprio_entity, run_list);
	next_p = container_of(next_entity, struct task_struct, myprio);
	pass_min = next_entity->pass;
	stride_min = next_entity->stride;
	
	for(i=0;i<myprio_rq->nr_running;i++){
		myprio_queue = myprio_queue->next;
		entity = container_of(myprio_queue, struct sched_myprio_entity, run_list);
		// if there's smaller pass value,
		// make it pass_min, stride_min
		// and set that entity to next_entity
		if(entity->pass < pass_min){
			pass_min = entity->pass;
			stride_min = entity->stride;
			next_entity = entity;
		}
		// if minimum value is more than 2,
		// select the one who's stride is smaller
		else if(entity->pass == pass_min){
			if(entity->stride < stride_min){
				stride_min = entity->stride;
				next_entity = entity;
			}
		}
	}
	next_p = container_of(next_entity, struct task_struct, myprio);
	printk(KERN_INFO"***[MYPRIO] pick_next_task: cpu=%d, prev->pid=%d, next_p->pid=%d, next_pass=%u, next_stride=%u, nr_running=%d\n", cpu_of(rq), prev->pid, next_p->pid, next_entity->pass, next_entity->stride, myprio_rq->nr_running);
	// return the picked one
	return next_p;	
}
void put_prev_task_myprio(struct rq *rq, struct task_struct *p) {
	printk(KERN_INFO "***[MYPRIO] put_prev_task: do_nothing, p->pid=%d\n",p->pid);
}
int select_task_rq_myprio(struct task_struct *p, int cpu, int sd_flag, int flags){return task_cpu(p);}
void set_curr_task_myprio(struct rq *rq){
	printk(KERN_INFO"***[MYPRIO] set_curr_task_myprio\n");
}
void task_tick_myprio(struct rq *rq, struct task_struct *p, int queued) {
	update_curr_myprio(rq);
}
void prio_changed_myprio(struct rq *rq, struct task_struct *p, int oldprio) { }
void switched_to_myprio(struct rq *rq, struct task_struct *p)
{
	resched_curr(rq);
}

const struct sched_class myprio_sched_class={
    .next = &fair_sched_class,
    .enqueue_task = enqueue_task_myprio,
    .dequeue_task = dequeue_task_myprio,
    .check_preempt_curr = check_preempt_curr_myprio,
    .pick_next_task = pick_next_task_myprio,
    .put_prev_task = put_prev_task_myprio,
#ifdef CONFIG_SMP
    .select_task_rq = select_task_rq_myprio,
#endif
    .set_curr_task = set_curr_task_myprio,
    .task_tick = task_tick_myprio,
    .prio_changed = prio_changed_myprio,
    .switched_to = switched_to_myprio,
    .update_curr = update_curr_myprio,
};
