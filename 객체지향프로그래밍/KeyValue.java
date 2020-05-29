

import java.util.StringTokenizer;

public class KeyValue {

	private	String key,value;
	
	public KeyValue(String input){
		StringTokenizer st = new StringTokenizer(input, "=");
		
		while(st.hasMoreTokens()) {
			this.key=st.nextToken();
			this.value=st.nextToken();
		}
	}
	
	public KeyValue(String key, String value){
		this.key=key;
		this.value=value;
	}

	public String getKey() {
		return this.key;
	}
	
	public String getValue() {
		return this.value;
	}
}
