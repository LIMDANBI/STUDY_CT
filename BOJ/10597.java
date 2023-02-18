import java.io.*;
import java.util.*;

public class Main {
	
	static int N, len;
	static boolean[] isuse;
	static List<Integer> nums = new ArrayList<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String seq = br.readLine();
		len = seq.length();
		if(len>9) len-=(len-9)/2;
		isuse = new boolean[len+1];
		solution(seq);
		br.close();
	}

	private static void solution(String seq) {
		if(seq.equals("")) {
			for(int i=0; i<len; i++) System.out.print(nums.get(i) + " ");
			System.exit(0);
		}
		
	    int num = 0;
	    for(int i=1; i<=2; i++){
	        num = Integer.parseInt(seq.substring(0, i));
	        if(num<=len && !isuse[num]){
	            isuse[num] = true;
	            nums.add(num);
	            solution(seq.substring(i));
	            isuse[num] = false;
	            nums.remove(nums.size()-1);
	        }
	        if(seq.length() == i) break;
	    }
	}
}