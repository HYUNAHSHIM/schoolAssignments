import java.util.Random;

public class Student implements Voter{
	
	public String name;//student's name
	public int id;//student's identification
	public Department dp;//student's department
	
	public void store(String name, int id, Department dp) {//input student's information
		this.name=name;
		this.id=id;
		this.dp=dp;
	}
	
	public void vote(Department dp) {//vote by using random
		Random random = new Random();
		int v = random.nextInt(dp.can.size());
		dp.can.get(v).nVote++;	
	}
	
	public int compareTo(Candidate c) {//compareTo function from comparable interface
		return 0;
	}
	
}
