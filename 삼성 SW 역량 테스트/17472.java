import java.io.*;
import java.util.*;

public class Main {
	
	static class Bridge implements Comparable<Bridge>{
		int from, to, len;
		public Bridge(int from, int to, int len) {
			this.from = from;
			this.to = to;
			this.len = len;
		}

		@Override
		public int compareTo(Bridge o) {
			if(this.len == o.len ) {
				if(this.to == o.to) return this.to - o.to;
				return this.from - o.from;
			} return this.len - o.len;
		}
	}
	
	static PriorityQueue<Bridge> pq = new PriorityQueue<>();
	static final int dy[] = { -1, 0, 1, 0 };
	static final int dx[] = { 0, -1, 0, 1 };
	static final int MAXISLAND = 8;
	static final int SEA = 0;
	static final int LAND = 1;
	
	static int N, M;
	static int[][] map;
	static int[] root = new int[MAXISLAND];
	
	static void solution() {
		
	    // 1. grouping
		int island_num = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == LAND) grouping(i, j, ++island_num); // 각 섬에 대표 번호를 매김 (start with 2)
			}
		}

		// 2. 다리 후보 선정
		make_candidates();

		// 3. MST로 다리 만들기
		System.out.println(make_bridge(island_num-2));
		
	}

	static void grouping(int y, int x, int num) {
		if (y < 0 || y >= N || x < 0 || x >= M) return; // 범위를 벗어나는 경우
		if (map[y][x] != LAND) return; // 땅이 아닌 경우
		map[y][x] = num;
		for (int d = 0; d < 4; d++) grouping(y + dy[d], x + dx[d], num);
	}
	
	static void make_candidates() {
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				
				if (map[y][x] == SEA) continue; // 바다인 경우
				
				int from = map[y][x]; // 출발지
				int to, len;
				for (int d = 0; d < 2; d++) { // 상,좌 만 탐색 (겹치는 다리를 없도록 하기 위해)
					to = 0; len = 0; // 도착지, 다리 길이

					int ny = y, nx = x;
					while (true) {
						ny+=dy[d]; nx+=dx[d]; // move
						len++; // 이동 거리
						if (ny < 0 || ny >= N || nx < 0 || nx >= M ) break; // 범위를 벗어나는 경우
						if (map[ny][nx] == from) break; // 같은 섬인 경우
						if (map[ny][nx] > LAND) { // 다른 섬에 도착한 경우
							if(--len > 1) to = map[ny][nx]; // 다리의 길이는 2 이상
							break;
						}
					} 
					if (to != 0) pq.add(new Bridge(from, to, len));
				}
			}
		}
	}
	
	static int find_(int x) {
		if (x == root[x]) return x;
		return root[x] = find_(root[x]);
	}
	
	static void union_(int x, int y) {
		root[find_(x)] = find_(y);
	}
	
	static int make_bridge(int need) {
		for (int i = 2; i < MAXISLAND; i++) root[i] = i; // union-find를 위한 초기화
		int ans = 0, bridge_num = 0;
		while (!pq.isEmpty() && bridge_num != need) {
			int len = pq.peek().len;
			int from = pq.peek().from;
			int to = pq.peek().to;
			pq.poll();

			if (find_(from) != find_(to)) { // 연결되지 않은 경우
				ans += len;
				bridge_num++;
				union_(from, to); // 연결
			}
		}
		if (bridge_num != need) return -1; // 모든 섬을 연결하는 것이 불가능한 경우
		return ans;
	}
	
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[N][M];
		
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < M; j++) map[i][j] = Integer.parseInt(st.nextToken());
		}
		solution(); //모든 섬을 연결하는 다리 길이의 최솟값
	}
}