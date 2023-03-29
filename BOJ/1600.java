import java.io.*;
import java.util.*;

public class Main {
	
	static final int dy[] = {-1, 1, 0, 0, -2, -2, -1, -1, 1, 1, 2, 2};
	static final int dx[] = {0, 0, -1, 1, -1, 1, -2, 2, -2, 2, -1, 1};
	
	static int K, Y, X;
	static boolean[][] iswall;
	static int[][][] visitCnt;
	
	private static int solution() {
		ArrayDeque<int[]> q = new ArrayDeque<>(); // y, x, k, cnt
		q.push(new int[] {0, 0, K, 0});
		visitCnt[0][0][K] = 0;
		
		int ans = Integer.MAX_VALUE;
		while(!q.isEmpty()) {
			int y = q.peek()[0];
			int x = q.peek()[1];
			int k = q.peek()[2];
			int cnt = q.peek()[3];
			q.poll();
			
			if(y==Y-1 && x==X-1) ans = Math.min(ans, cnt);
			
			for(int d=0; d<4; d++) {
				int ny = y+dy[d];
				int nx = x+dx[d];
				
				if(ny<0 || ny>=Y || nx<0 || nx>=X || iswall[ny][nx]) continue;
				if(visitCnt[ny][nx][k]==0 || cnt+1 < visitCnt[ny][nx][k]) {
					q.offer(new int[] {ny, nx, k, cnt+1});
					visitCnt[ny][nx][k] = cnt+1;
				}
			}
			
			for(int d=4; d<dy.length; d++) {
				int ny = y+dy[d];
				int nx = x+dx[d];
				
				if(ny<0 || ny>=Y || nx<0 || nx>=X || iswall[ny][nx] || k==0) continue;					
				if(visitCnt[ny][nx][k-1]==0 || cnt+1 < visitCnt[ny][nx][k-1]) {
					q.offer(new int[] {ny, nx, k-1, cnt+1});
					visitCnt[ny][nx][k-1] = cnt+1;
				}
			}
		}
		if(ans!=Integer.MAX_VALUE) return ans; 
		return -1;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		K = Integer.parseInt(br.readLine());
		st = new StringTokenizer(br.readLine());
		X = Integer.parseInt(st.nextToken());
		Y = Integer.parseInt(st.nextToken());
		
		iswall = new boolean[Y][X];
		visitCnt = new int[Y][X][K+1];
		
		for(int i=0; i<Y; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<X; j++)
				iswall[i][j] = (Integer.parseInt(st.nextToken())==0 ? false:true);
		}
		System.out.println(solution());
	}
}