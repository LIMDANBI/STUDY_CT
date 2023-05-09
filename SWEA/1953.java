import java.io.*;
import java.util.*;

public class Solution {
	
	// connected[d][before_type][next_type] ;  b-(d)->n
	static final boolean T = true;
	static final boolean F = false;
	static final boolean[][][] connected = {
			{{T, T, F, F, T, T, F}, // 상
			{T, T, F, F, T, T, F}, 
			{F, F, F, F, F, F, F}, 
			{T, T, F, F, T, T, F}, 
			{F, F, F, F, F, F, F}, 
			{F, F, F, F, F, F, F}, 
			{T, T, F, F, T, T, F}},
			
			{{T, T, F, T, F, F, T}, // 하 
			{T, T, F, T, F, F, T}, 
			{F, F, F, F, F, F, F}, 
			{F, F, F, F, F, F, F}, 
			{T, T, F, T, F, F, T}, 
			{T, T, F, T, F, F, T}, 
			{F, F, F, F, F, F, F}},
			
			{{T, F, T, T, T, F, F}, // 좌
			{F, F, F, F, F, F, F}, 
			{T, F, T, T, T, F, F},
			{F, F, F, F, F, F, F},  
			{F, F, F, F, F, F, F},  
			{T, F, T, T, T, F, F}, 
			{T, F, T, T, T, F, F}},
			
			{{T, F, T, F, F, T, T}, // 우 
			{F, F, F, F, F, F, F}, 
			{T, F, T, F, F, T, T}, 
			{T, F, T, F, F, T, T}, 
			{T, F, T, F, F, T, T}, 
			{F, F, F, F, F, F, F},  
			{F, F, F, F, F, F, F}}
	};
	
	static final int[][] dy = {
			{-1, 1, 0, 0}, // 상하좌우
			{-1, 1, 0, 0}, // 상하
			{0, 0, 0, 0}, // 좌우
			{-1, 0, 0, 0}, // 상우
			{0, 1, 0, 0}, // 하우
			{0, 1, 0, 0}, // 하좌
			{-1, 0, 0, 0} // 상좌
	};
	static final int[][] dx = {
			{0, 0, -1, 1}, // 상하좌우
			{0, 0, 0, 0}, // 상하
			{0, 0, -1, 1}, // 좌우
			{0, 0, 0, 1}, // 상우
			{0, 0, 0, 1}, // 하우
			{0, 0, -1, 0}, // 하좌
			{0, 0, -1, 0} // 상좌
	};
	
	static int[][] map;
	static boolean[][] visited;
	static int N, M, R, C, L;
	
	private static int solution() { // 탈주범이 위치할 수 있는 장소의 개수
		int ans = 1;
		
		ArrayDeque<int[]> now = new ArrayDeque<>();
		ArrayDeque<int[]> next = new ArrayDeque<>();
		
		now.offer(new int[] {R, C});
		visited[R][C] = true;
		
		while(--L>0) {
			while(!now.isEmpty()) {
				int y = now.peek()[0];
				int x = now.peek()[1];
				int type = map[y][x]-1; // 터널 구조물 타입
				now.poll();
				
				for(int d=0; d<dy[type].length; d++) {
					int ny = y+dy[type][d];
					int nx = x+dx[type][d];
					if(ny<0 || ny>=N || nx<0 || nx>=M) continue; // 범위를 벗어나는 경우
//					System.out.println(d + " " + type + "  " + map[ny][nx]);
					if(visited[ny][nx] || map[ny][nx]==0 || !connected[d][type][map[ny][nx]-1]) continue; // 이미 방문한 경우, 터널이 아닌 경우
					
					ans++;
					visited[ny][nx] = true;
					next.offer(new int[] {ny, nx});
				}				
			}
			while(!next.isEmpty()) now.offer(next.poll());
		}
		return ans;
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		int T = Integer.parseInt(br.readLine());
		for(int t=1; t<=T; t++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			R = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());
			map = new int[N][M];
			visited = new boolean[N][M];
			
			for(int i=0; i<N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<M; j++) map[i][j] = Integer.parseInt(st.nextToken());
			}
			sb.append("#" + t + " " + solution() + "\n");
		}
		System.out.println(sb.toString());
	}
}