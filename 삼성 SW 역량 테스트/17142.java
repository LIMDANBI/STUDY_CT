import java.io.*;
import java.util.*;

public class Main {
	
	static class DATA{
		int y, x, sec;

		public DATA(int y, int x, int sec) {
			super();
			this.y = y;
			this.x = x;
			this.sec = sec;
		}
	}
	
	static final int INF = 1000000001;
	static final int EMPTY = 0;
	static final int WALL = 1;
	static final int VIRUS = 2;
	static final int VISITED = 3;
	
	static int N, M;
	static int ans=INF;
	static int empty_cnt = 0;
	
	static int[][] lab;
	static int[][] copy_lab;
	
	static List<Integer> active = new ArrayList<>();
	static List<int []> virus = new ArrayList<>();
	
	static int dy[] = { -1,1,0,0 };
	static int dx[] = { 0,0,-1,1 };

	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		lab = new int[N][N];
		copy_lab = new int[N][N];
		
		// input 
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				lab[i][j] = Integer.parseInt(st.nextToken());
				if (lab[i][j] == WALL)  continue; // 벽인 경우
				if (lab[i][j] == VIRUS) virus.add(new int[] { i, j }); // 바이러스 위치
				else empty_cnt++; 
			}
		}
		
		// solution
		solution(0, 0);
		
		// output
		if (ans == INF) System.out.println(-1); // 바이러스를 어떻게 놓아도 모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우
		else System.out.println(ans); // 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간
	}

	private static void solution(int cnt, int idx) {
		if (cnt == M) { // 바이러스 M개를 활성 상태로 변경한 경우
			ans = Math.min(ans, spread_virus()); // 바이러스를 퍼뜨림
			return;
		}
		for (int i = idx; i < virus.size(); i++) {
			active.add(i); // 바이러스 활성화
			solution(cnt + 1, i + 1);  // 조합 구현 
			active.remove(active.size()-1); // 바이러스 비활성화
		}
	}

	private static int spread_virus() {
		// 1. copy
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) copy_lab[i][j] = lab[i][j];
		}

		Queue<DATA> q = new LinkedList<>();
		for (int i = 0; i < active.size(); i++) {
			int num = active.get(i); // 활성화한 바이러스
			int y = virus.get(num)[0];
			int x = virus.get(num)[1];
			copy_lab[y][x] = VISITED;
			q.offer(new DATA(y, x, 0));
		}
		if (empty_cnt == 0) return 0;

		int sec = 0; // 걸린 시간
		int spread = 0;
		while (!q.isEmpty()) {
			int y = q.peek().y;
			int x = q.peek().x;
			int s = q.peek().sec;
			q.poll();
			
			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue; // 범위를 벗어나는 경우
				if (copy_lab[ny][nx] == WALL || copy_lab[ny][nx] == VISITED) continue; // 벽인 경우,이미 방문한 경우
				if (copy_lab[ny][nx] == EMPTY) {
					spread++; // 바이러스 전파
					sec = Math.max(sec, s + 1); // 비활성화 바이러스가 활성화 되는 시간은 계산 x
				}
				copy_lab[ny][nx] = VISITED; // 바이러스 전파, 비활성 바이러스 -> 활성화 
				q.offer(new DATA(ny, nx, s + 1));
			}
		} 
		
		if (spread == empty_cnt) return sec; // 바이러스가 모두 전파된 경우 
		return INF; // 바이러스가 모두 전파될 수 없는 경우
	}

}