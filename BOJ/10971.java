package solution;

import java.io.*;
import java.util.*;

public class Main {
	
	static final int INF = 1000000001;
	
	static int N, ans=INF;
	static int[][] cost;
	static boolean[] visit;
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		N = Integer.parseInt(br.readLine());
		cost = new int[N][N];
		visit = new boolean[N];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) cost[i][j] = Integer.parseInt(st.nextToken());
		}
		solution(0, 1, 0);
		System.out.println(ans);
	}

	private static void solution(int now, int cnt, int totalCost) {
		if(cnt == N) {
			if(cost[now][0] != 0) {
				ans = Math.min(ans, totalCost+cost[now][0]);
			}
			return ;// 돌아갈 수 있는 경우 
		}
		
		for(int next=1; next<N; next++) {
			if(visit[next] || cost[now][next]==0) continue;
			visit[next] = true;
			solution(next, cnt+1, totalCost+cost[now][next]);
			visit[next] = false;
		}
	}
}