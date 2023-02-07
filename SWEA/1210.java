import java.io.*;
import java.util.*;

public class Solution {
	
	static StringBuilder sb = new StringBuilder();
	static final int MAX = 100;
	static final int UP = 0;
	static final int RIGHT = 1;
	static final int LEFT = 2;

	static int ans = 0;
	static int[][] ladder = new int[MAX][MAX];

	public static void main(String[] args) throws Exception{
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null; 
		
		int row = 0, col = 0;
		for(int t=1; t<=10; t++) {
			br.readLine(); // 문제의 입력 형식을 맞추기 위해 
			for(int i=0; i<MAX; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<MAX; j++) {
					ladder[i][j] = Integer.parseInt(st.nextToken());
					if(ladder[i][j] == 2) {
						row = i; col = j;
					}
				}
			} 
			solution(row, col, UP);
			sb.append("#").append(t).append(" ").append(ans).append("\n");
		}
		System.out.println(sb.toString());
	}

	static void solution(int y, int x, int d) {
		if(y == 0) {
			ans = x;
			return ;
		}
		if(x-1>=0 && ladder[y][x-1] == 1 && d!=RIGHT) solution(y, x-1, LEFT);
		else if(x+1<MAX && ladder[y][x+1] == 1 && d!=LEFT) solution(y, x+1, RIGHT);
		else solution(y-1, x, UP);
	}
}