import java.io.*;
import java.util.*;

public class Main {
	
	static int N;
	static StringBuilder sb = new StringBuilder();

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));		
		N = Integer.parseInt(br.readLine());
		
		String perm;
		for(int i=0; i<N; i++) {
			perm = br.readLine();
			sb.append(solution(perm)+"\n");
		}
		System.out.println(sb.toString());
		br.close();
	}

	static String solution(String perm) {
		
		int last_idx = perm.length()-1;
		char[] permArr = perm.toCharArray();
		
		// step 1 꼭대기를 찾음
		int i = last_idx;
		while(i>0 && permArr[i] <= permArr[i-1]) i--;
		if(i == 0) return "USELESS";
		
		// step 2 교환할 자리를 찾음
		int j = last_idx;
		while(j>0 && permArr[j] <= permArr[i-1]) j--;
		
		// step 3 swap
		swap(permArr, i-1, j);
		
		// step 4 sort
		int k = last_idx;
		while(i < k) swap(permArr, i++, k--);
		
		return new String(permArr);
	}
	
	static void swap(char[] permArr, int i, int j) {
		char tmp = permArr[i];
		permArr[i] = permArr[j];
		permArr[j] = tmp;
	}
}