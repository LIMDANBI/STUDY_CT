import java.io.*;
import java.util.*;

public class Main {
	
	private static final int INF = 1000000001;
	
	private static boolean[][] border;
	private static int[] population;
	private static int[][] A;
	private static int dx[] = {1, 1, -1, -1};
	private static int dy[] = {1, -1, -1, 1};
	private static int N, total=0, ans = INF;

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		// input
		N = Integer.parseInt(st.nextToken());
		A = new int[N+1][N+1];
		for (int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 1; j <= N; j++) {
				A[i][j] = Integer.parseInt(st.nextToken()); 
	            total+=A[i][j];
	        }
		}
		solution();
	}

	private static void solution() {
		for (int d1=1; d1<N; d1++) { // d1, d2 ≥ 1
			for (int d2=1; d2<N; d2++) {
				for (int x=1; x<=N-d1-d2; x++) { // 1 ≤ x < x+d1+d2 ≤ N
					for (int y=d1+1; y<=N-d2; y++) // 1 ≤ y-d1 < y < y+d2 ≤ N
						ans = Math.min(ans, diff(x, y, d1,d2));
				}
			}
		} System.out.println(ans);
	}

	private static int diff(int x, int y, int d1, int d2) {
	    population = new int[5];
	    border = new boolean[N+1][N+1];

	    int nx = x, ny = y;
	    int mvoe_cnt[] = {d2, d1, d2, d1};
	    for(int d=0; d<4; d++){
	        for(int i=0; i<mvoe_cnt[d]; i++){
	            nx+=dx[d]; ny+=dy[d];
	            border[nx][ny] = true; // 경계 설정
	        }
	    }

	    // 좌측 상단 (1번 선거구)
	    for(int r=1; r<x+d1; r++){ // 1 ≤ r < x+d1
	        for(int c=1; c<=y && !border[r][c]; c++) population[0]+=A[r][c]; //  1 ≤ c ≤ y
	    }

	    // 우측 상단 (2번 선거구)
	    for(int r=1; r<=x+d2; r++){ // 1 ≤ r ≤ x+d2
	        for(int c=N; c>y && !border[r][c]; c--) population[1]+=A[r][c]; //  y < c ≤ N
	    }

	    // 좌측 하단 (3번 선거구)
	    for(int r=x+d1; r<=N; r++){ // x+d1 ≤ r ≤ N
	        for(int c=1; c<y-d1+d2 && !border[r][c]; c++) population[2]+=A[r][c]; // 1 ≤ c < y-d1+d2
	    }

	    // 우츨 하단 (4번 선거구)
	    for(int r=x+d2+1; r<=N; r++){ // x+d2 < r ≤ N
	        for(int c=N; c>=y-d1+d2 && !border[r][c]; c--) population[3]+=A[r][c]; // y-d1+d2 ≤ c ≤ N
	    }

	    population[4] = total;
	    for(int i=0; i<4; i++) population[4]-=population[i]; // 5번 선거구
	    Arrays.sort(population);
	    return population[4]-population[0]; // 최대 - 최소
	}	
}