import java.awt.List;
import java.io.*;
import java.util.*;

public class Main {
	
	static StringBuilder sb = new StringBuilder();
	
    static final int dr[] = { -1, 0, 1, 0 }; // 상 우 하 좌
    static final int dc[] = { 0, 1, 0, -1 };
	
	static int R, C;
	static int ans = 0;
	static int[][] map;
	static boolean[] isused;
	static boolean[][] visited;

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		map = new int[R][C];
		isused = new boolean[27]; // 알파벳 사용 여부
		visited = new boolean[R][C];
		ans = 0; // init
		
		for(int r=0; r<R; r++) {
			String line = br.readLine();
			for(int c=0; c<C; c++) map[r][c] = line.charAt(c)-'A';
		}
		
		visited[0][0] = true;
		isused[map[0][0]] = true;
		solution(0, 0, 1);
		System.out.println(ans);
	}

	private static void solution(int r, int c, int cnt) {
		ans = Math.max(ans, cnt);
		for(int d=0; d<4; d++) {
			int nr = r+dr[d];
			int nc = c+dc[d];
			if(nr < 0 || nr>=R || nc<0 || nc>=C) continue; // 범위를 벗어나는 경우
			if(isused[map[nr][nc]]|| visited[nr][nc]) continue; //이미 사용한 경우, 이미 방문한 경우
			visited[nr][nc] = true;
			isused[map[nr][nc]] = true;
			solution(nr, nc, cnt+1);
			visited[nr][nc] = false;
			isused[map[nr][nc]] = false;
		}
	}
}