import java.io.*;
import java.util.*;

public class Main {
	
	static final int INF = 1000000000;
	
	static int N;
	static int[][] cost, dp;
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		cost = new int[N][N];
		dp = new int[N][1<<N];

		for(int i=0; i<N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) cost[i][j] = Integer.parseInt(st.nextToken());
		}
		System.out.println(solution(0, 1));
		br.close();
	}

	private static int solution(int now, int visit) {
		if(visit == (1<<N)-1) {
			if(cost[now][0] == 0) return INF;
			return cost[now][0];
		}
		
		if(dp[now][visit]!=0) return dp[now][visit];
		
		dp[now][visit] = INF;
		for(int next=0; next<N; next++) {
			if(cost[now][next]==0 || (visit&(1<<next))!=0) continue;
			 dp[now][visit] = Math.min(dp[now][visit], cost[now][next]+solution(next, visit|(1<<next)));
		}
		
		return dp[now][visit];
	}
}