

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.*;

public class LetterTransformator {
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		String data="";
		
		Scanner properties = null;
		Scanner template_file = null;
		PrintWriter output = new PrintWriter("output_file.txt");
		
		try {
			properties = new Scanner(new FileInputStream(args[0]));
			template_file = new Scanner(new FileInputStream(args[1]));
		}
		catch(FileNotFoundException e) {
			System.out.println("File not found.");
			System.exit(0);
		}
		
		ArrayList<KeyValue> list = new ArrayList<KeyValue>();
		while(properties.hasNext()) {
			list.add(new KeyValue(properties.nextLine()));
		}
		
		while(template_file.hasNext()) {
			data = template_file.nextLine();
			
			if(data.indexOf("{")==-1) {
				output.println(data);
			}
			
			while(data.indexOf("{")!=-1) {
				
				int start= data.indexOf("{");
				int end=data.indexOf("}");
				String keyFind=data.substring(start,end+1);
								
				for(int i=0;i<list.size();i++) {
					if(list.get(i).getKey().equals(keyFind.substring(1,keyFind.length()-1))) {
						data=data.replace(keyFind, list.get(i).getValue());
						if(data.indexOf("{")==-1) output.println(data);
						break; 
						}
					}			
				}	
			}
		properties.close();
		template_file.close();
		output.close();
	}
}
