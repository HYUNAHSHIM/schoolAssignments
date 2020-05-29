
public class Candidate extends Student {
	public int nVote;
	
	public int compareTo(Candidate c) {//from interface comparable
		return this.nVote - c.nVote;
	}
}
