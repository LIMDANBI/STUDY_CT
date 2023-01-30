import java.io.*;
import java.util.*;

public class Main {
	
	static final int WALL =1 ;
	static final int MAX =51 ;	
	
	static class DATA{
		int r, c, d;

		public DATA(int r, int c, int d) {
			super();
			this.r = r;
			this.c = c;
			this.d = d;
		}
		
	}
	
	static int N, M, ans=0;
	static int r, c, d;
	static int map[][];
	static boolean visited[][];
	static int dy[] = {-1, 0, 1, 0}; // 북 동 남 서
	static int dx[] = {0, 1, 0, -1};

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[N][M];
		visited = new boolean[N][M];
		
		st = new StringTokenizer(br.readLine());
		r = Integer.parseInt(st.nextToken());
		c = Integer.parseInt(st.nextToken());
		d = Integer.parseInt(st.nextToken());
		
	    for(int i=0; i<N; i++){
	    	st = new StringTokenizer(br.readLine());
	        for(int j=0; j<M; j++) {
	        	map[i][j] = Integer.parseInt(st.nextToken());
	        }
	    }
		solution();
	}

	private static void solution() {
		Deque<DATA> q =  new ArrayDeque<>();
	    q.addLast(new DATA(r, c, d));
	    visited[r][c] = true;

	    int ans = 1;
	    while(!q.isEmpty()){
	        int y = q.peek().r;
	        int x = q.peek().c;
	        int dir = q.peek().d;
	        q.poll();

	        boolean flag = true;
	        int left = dir;
	        for(int i=0; i<4; i++){
	            left = (left+3)%4; // 반시계 방향 탐색 (2-1, 2-2)
	            int ny = y+dy[left];
	            int nx = x+dx[left];

	            if(ny<0 || ny>=N || nx<0 || nx>=M) continue; // 범위를 벗어나는 경우
	            if(visited[ny][nx] || map[ny][nx]==WALL) continue; // 이미 청소한 경우, 벽인 경우
	            visited[ny][nx] = true; // 청소
	            q.addLast(new DATA(ny, nx, left));
	            flag = false; ans++;
	            break;
	        }

	        if(flag){ // 네 방향 모두 청소가 이미 되어있거나 벽인 경우
	            int back = (dir+2)%4; // 뒤쪽
	            int ny = y+dy[back];
	            int nx = x+dx[back];

	            if(ny<0 || ny>=N || nx<0 || nx>=M || map[ny][nx]==WALL) break; // 네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽이 벽이라 후진도 할 수 없는 경우
	            q.addLast(new DATA(ny, nx, dir)); // 후진 가능한 경우
	        }
	    }
	    System.out.println(ans);
	}
}
