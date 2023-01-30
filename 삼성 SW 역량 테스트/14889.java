import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N, ans=Integer.MAX_VALUE;
	static int[][] score;
	static boolean[] start_team;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		score = new int[N][N];
		start_team = new boolean[N];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				score[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		solution(0, 0);
		System.out.println(ans);
	}

	private static void solution(int idx, int cnt) {
		if (cnt == N / 2) {
			int start = 0, link = 0;
			for (int i = 0; i < N; i++) {
				for (int j = i + 1; j < N; j++) {
					if (start_team[i] == start_team[j]) {
						if (start_team[i]) start += (score[i][j] + score[j][i]);
						else link += (score[i][j] + score[j][i]);
					}
				}
			}
			ans = Math.min(ans, Math.abs(start - link));
			return;
		}
		for (int i = idx; i < N; i++) {
			start_team[i] = true;
			solution(i + 1, cnt + 1);
			start_team[i] = false;
		}
	}
}