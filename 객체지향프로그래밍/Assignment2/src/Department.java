import java.util.ArrayList;

public class Department {
	public String name;//name of department
	public ArrayList<Candidate> can = new ArrayList<Candidate>();
	public ArrayList<Student> stu = new ArrayList<Student>();
	
	public Candidate mostVote() {//select candidate who has most vote number
		Candidate c=this.can.get(0);
		for(int i=0; i<this.can.size();i++) {
			if(this.can.get(i).compareTo(c)>0) c=this.can.get(i);
		}
		return c;
	}
}
