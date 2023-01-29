import java.io.*;
import java.util.*;

public class Main {
	
	static final int ENEMY = 1;
	static final int EMPTY = 0;
	
	static class Attack implements Comparable<Attack>{
		int dist, r, c;

		public Attack(int dist, int r, int c) {
			super();
			this.dist = dist;
			this.r = r;
			this.c = c;
		}

		@Override
		public int compareTo(Attack o) {
			if(this.dist == o.dist) return this.c - o.c; // 열이 더 작은 값
			return this.dist-o.dist; // 거리가 더 작은 값
		}
	}
	
	static int ans = 0;
	static int N, M, D;
	static int[][] map, copy_map;
	static List<int[]> archer = new ArrayList<int[]>();
	static List<int[]> enemy = new ArrayList<int[]>();

	public static void main(String[] args) throws Exception {
		
		// 1. input
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        
        map = new int[N][M];
        copy_map = new int[N][M];
        
        for(int i=0; i<N; i++) {
        	st = new StringTokenizer(br.readLine());
        	for(int j=0; j<M; j++) {
        		map[i][j] = Integer.parseInt(st.nextToken());
        		if(map[i][j] == ENEMY) enemy.add(new int[]{i, j}); // 적의 위치 저장
        	}
        }
        
        // 2. solution
        solution(0, 0);
        System.out.println(ans);
        br.close();
	}
	
	private static int attack_enemy(int move) {
		int kill = 0;
		int ar, ac; // 궁수의 위치
		List<int[]> attack_pos = new ArrayList<int[]>();; // 공격할 적들의 위치 

		for (int a = 0; a < (int)archer.size(); a++) { // 궁수 
			ar = archer.get(a)[0]-move;
			ac = archer.get(a)[1];
					
			int er, ec, dist; // 적의 위치
			PriorityQueue<Attack> pq = new PriorityQueue<>(); // dist, row, col 
			for (int e = 0; e < (int)enemy.size(); e++) { // 적
				er = enemy.get(e)[0];
				ec = enemy.get(e)[1];
				dist = Math.abs(ar - er) + Math.abs(ac - ec); // 거리 계산
				if (dist > D || ar<=er || map[er][ec]==EMPTY) continue; // 공격 거리 D를 초과하는 경우, 격자판을 벗어난 적인 경우, 이미 공격한 적인 경우
				pq.add(new Attack(dist, er, ec)); 
			}
			if (pq.isEmpty()) continue;
			int r = pq.peek().r;
			int c = pq.peek().c;
			attack_pos.add(new int[] { r,c });
		}

		for (int i = 0; i < attack_pos.size(); i++) { // 모든 궁수는 동시에 공격
			int r = attack_pos.get(i)[0];
			int c = attack_pos.get(i)[1];
			if (map[r][c] == EMPTY) continue;
			map[r][c] = 0; // 선택된 적 공격 (같은 적이 여러 궁수에게 공격당할 수 있음)
			kill++;
		}
		return kill; // 제거한 적의 수
	}
	
	private static int simulation() {
		int kill = 0;
		for (int move = 0; move < N; move++) {
			kill += attack_enemy(move); // 적 공격 + 이동 (적 대신 궁수가 이동하는 것으로 대체)
		} return kill;
	}
	
	private static void solution(int cnt, int idx) {
		if (cnt == 3) { // 모든 궁수를 배치한 경우

			// 1. copy 
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) copy_map[i][j] = map[i][j];
			}

			// 2. simulation
			ans = Math.max(ans, simulation());

			// 3. recovery
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) map[i][j] = copy_map[i][j];
			}

			return;
		}
		for (int col = idx; col < M; col++) {
			archer.add(new int[]{N, col}); // 궁수 배치
			solution(cnt + 1, col + 1); // 다음 궁수 배치
			archer.remove(archer.size()-1);
		}
	}
}