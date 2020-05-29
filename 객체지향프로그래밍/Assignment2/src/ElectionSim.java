import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;

public class ElectionSim {
	String departFile;
	String stuFile;
	String output;
	ArrayList<Department> dep = new ArrayList<Department>();
	ArrayList<Candidate> can = new ArrayList<Candidate>();
	
	public ElectionSim(String departFi, String stuFi, String outFi) {
		this.departFile = departFi;//input file name
		this.stuFile = stuFi;
		this.output = outFi;
		Scanner departF = null;//to read department file
		try {
			departF = new Scanner(new FileInputStream(departFile),"UTF-8");
		}
		catch(FileNotFoundException e) {
			System.out.println("File is not found");
			System.exit(0);
		}
		
		departF.nextLine();//read the first line
		while(departF.hasNext()) {
			Department d = new Department();
			String tmp;//variable to get line from file
			tmp = departF.nextLine();
			String[] tmp2 = tmp.split(",");//split the tmp with ","
			d.name=tmp2[1];
			this.dep.add(d);//add information about department
		}
		
		Scanner stuF = null;//to read student file
		try {
			stuF = new Scanner(new FileInputStream(stuFile),"UTF-8");
		}
		catch(FileNotFoundException e) {
			System.out.println("File is not found");
			System.exit(0);
		}
		stuF.nextLine();//read the first line
		while(stuF.hasNext()) {
			int d,i=0;//d for department number, i for index of tmp2
			String c, tmp;//c for store true or false, tmp for get line from file
			tmp = stuF.nextLine();
			String[] tmp2 = tmp.split(",");//split the tmp with ","
			Student s=new Student();
			s.id = Integer.parseInt(tmp2[i++]);
			d = Integer.parseInt(tmp2[i++]);
			s.name = tmp2[i++];
			c = tmp2[i++];
			this.dep.get(d-1).stu.add(s);//add information about student
			if(c.equals("TRUE")) {//if student is candidate
				Candidate candi = new Candidate();
				candi.id = s.id;
				candi.name = s.name;
				candi.dp = new Department();
				candi.dp.name = this.dep.get(d-1).name;
				this.dep.get(d-1).can.add(candi);//add information about candidate
			}
		}
	}
	
	public void saveData() throws IOException {
		FileWriter file = null;//to write in output file
		try {
			file = new FileWriter(this.output);
		}
		catch(IOException e) {
			System.out.println("File Not Found");
			System.exit(0);
		}
		for(int i=0;i<this.can.size();i++) {//write in output file
			file.write("======== Elected Candidate ========\r\n");
			file.write("Department name: "+ this.can.get(i).dp.name+"\r\n");
			file.write("name: "+this.can.get(i).name+"\r\n");
			file.write("Student_id: "+this.can.get(i).id+"\r\n");
			file.write("Votes: "+this.can.get(i).nVote+"\r\n");
			file.write("=============================\r\n");
		}
		file.flush();
	}
	
	public void runSimulation() {
		for(int i=0;i<this.dep.size();i++) {
			Iterator<Student> it= this.dep.get(i).stu.iterator();//iterator for student in department
			while(it.hasNext()) {//implement vote function
				 it.next().vote(this.dep.get(i));
			}
		}
		for(int i=0;i<this.dep.size();i++) {//add elected candidates in "can" array list
			can.add(this.dep.get(i).mostVote());
		}
		try{
			this.saveData();
		}
		catch(IOException e) {
			System.out.println("Error");
			System.exit(0);
		}
	}
}
