import java.io.*;
import java.util.*;

public class Main {
	
	static final int IMPOSSIBLE = 4;
	static int ans = IMPOSSIBLE;
	
	static int N, M, H;
	static boolean[][] isLine;
	
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
		isLine = new boolean[H+1][N+1];
		
		int a, b;
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			a = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			isLine[a][b] = true; // 입력으로 주어지는 가로선이 서로 연속하는 경우는 없음
		}
		
	    for(int maxcnt=0; maxcnt<4 && ans==IMPOSSIBLE; maxcnt++) solution(0, 1, maxcnt);
	    if(ans == IMPOSSIBLE) System.out.println(-1);
	    else System.out.println(ans);
		
	}
	
	static void solution(int cnt, int row, int maxcnt) {
	    if(cnt == maxcnt){
	        if(ispossible()) ans = maxcnt; // i번 세로선의 결과가 i번이 나오도록 사다리 게임을 조작하려면, 추가해야 하는 가로선 개수의 최솟값
	        return;
	    }
	    for (int a = row; a <= H; a++) {
			for (int b = 1; b < N; b++) {
				if (isLine[a][b] || isLine[a][b+1] || isLine[a][b-1]) continue; // 이미 가로선이 있는 경우, 서로 연속하는 경우
				isLine[a][b] = true;
				solution(cnt + 1, a, maxcnt);
				isLine[a][b] = false;
			}
		}
	}
	
	static boolean ispossible() {
		for (int n = 1; n <= N; n++) { // 세로선
			int col = n;
			for (int h = 1; h <= H; h++) {
				if (isLine[h][col]) col++;
				else if (isLine[h][col - 1]) col--;
			}
			if (col != n) return false; // i번 세로선의 결과 != i번
		} return true;
	}
}