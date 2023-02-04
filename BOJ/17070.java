import java.io.*;
import java.util.*;

public class Main {
	
	static final int WALL = 1;
	
	static int N;
	static int ans=0;
	static int home[][];
	
	public static void main(String[] args) throws Exception {
		
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		home = new int[N][N];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				home[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		dfs(0, 1, 0);
		System.out.println(ans);
	}

	private static void dfs(int y, int x, int d) {
		if(y>=N || x>=N || home[y][x]==WALL) return;
		if(d==2 && (home[y-1][x]==WALL || home[y][x-1]==WALL)) return;
		if(y==N-1 && x==N-1) { // 파이프를 이동을 완료한 경우
			ans++;
			return;
		}
		if(d ==0) { // 가로 
			dfs(y, x+1, 0);
			dfs(y+1, x+1, 2);			
		}
		else if(d==1) { // 세로 
			dfs(y+1, x, 1);
			dfs(y+1, x+1, 2);
		}
		else if(d==2) { // 대각선 
			dfs(y, x+1, 0);
			dfs(y+1, x, 1);
			dfs(y+1, x+1, 2);
		}
	}
}