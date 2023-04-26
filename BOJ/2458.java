import java.io.*;
import java.util.*;

public class Main {
	
	static int N, M;
	static boolean[][] check;
	static List<Integer>[] small, big;
	
	private static int solution() {
		
        ArrayDeque<Integer> q = new ArrayDeque<>();
        
        // 작은 것들을 통해 간접 비교 가능한지 체크
		for(int b=1; b<=N; b++) {
			for(int i=0; i<small[b].size(); i++) {
				int a = small[b].get(i);
				check[b][a] = true;
				q.offer(a);
			}
			
			while(!q.isEmpty()) {
				int n = q.poll();
				for(int i=0; i<small[n].size(); i++) {
					int a = small[n].get(i);
					if(check[b][a]) continue;
					check[b][a] = true;
					q.offer(a);
				}
			}
		}
		
        // 큰 것들을 통해 간접 비교 가능한지 체크
		for(int a=1; a<=N; a++) {
			for(int i=0; i<big[a].size(); i++) {
				int b = big[a].get(i);
				check[a][b] = true;
				q.offer(b);
			}
			
			while(!q.isEmpty()) {
				int n = q.poll();
				for(int i=0; i<big[n].size(); i++) {
					int b = big[n].get(i);
					if(check[a][b]) continue;
					check[a][b] = true;
					q.offer(b);
				}
			}
		}
				
		int ans = 0;
		for(int i=1; i<=N; i++) {
			int cnt = 0;
			for(int j=1; j<=N; j++) {
				if(i==j) continue;
				if(check[i][j]) cnt++;
			} if(cnt==N-1) ans++;
		}
		return ans;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		StringTokenizer st = new  StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		check = new boolean[N+1][N+1];
		small = new ArrayList[N+1];
		big = new ArrayList[N+1];
		for(int n=1; n<=N; n++){ // 생성
			small[n] = new ArrayList<>();
			big[n] = new ArrayList<>();
		}
		
		for(int i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			small[b].add(a);
			big[a].add(b);
		}
		System.out.println(solution());
	}
}