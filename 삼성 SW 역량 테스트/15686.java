import java.io.*;
import java.util.*;

public class Main {
	
	private static final int HOME = 1;
	private static final int CHICKEN = 2;
	
	private static int N, M, ans=Integer.MAX_VALUE;
	private static int city[][];
	static List<int []> home = new ArrayList<int[]>();
	static List<int []> chicken = new ArrayList<int[]>();
	static List<int []> picked = new ArrayList<int[]>();
	
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		city = new int[N][N];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				city[i][j] = Integer.parseInt(st.nextToken());
				if(city[i][j] == HOME) home.add(new int[] {i,j});
				if(city[i][j] == CHICKEN) chicken.add(new int[] {i,j});
			}
		}
		solution(0, 0);
		System.out.println(ans);
	}

	private static void solution(int idx, int cnt) {
		if(cnt == M) { // 폐업시키지 않을 치킨집 M개를 고른 경우
			int res = 0;
			for(int h=0; h<home.size(); h++) {
				int min_dist = Integer.MAX_VALUE;
				for(int c=0; c<picked.size(); c++) {
					int dist = Math.abs(home.get(h)[0]-picked.get(c)[0]) + Math.abs(home.get(h)[1]-picked.get(c)[1]);
					min_dist = Math.min(min_dist, dist);
				}
				res+=min_dist;
			}
			ans = Math.min(ans, res);
			return ;
		}
		for(int i=idx; i<chicken.size(); i++) {
			picked.add(chicken.get(i));
			solution(i+1, cnt+1);
			picked.remove(picked.size()-1);
		}
	}
}