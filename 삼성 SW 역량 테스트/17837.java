import java.io.*;
import java.util.*;

public class Main {
    
	static class Chess{
		int y, x, dir;
		public Chess(int y, int x, int dir) {
			this.y = y;
			this.x = x;
			this.dir = dir;
		}
	}
	
	static final int dy[] = {0, 0, 0, -1, 1}; // 1부터 순서대로 →, ←, ↑, ↓
	static final int dx[] = {0, 1, -1, 0, 0};
	static final int WHITE = 0;
	static final int RED = 1;
	static final int BLUE = 2;
	
	static int N, K;
	static boolean iscontinue = true;
	
	static int[][] color;
	static Chess[] chess;
	static ArrayList<Integer>[][] map;

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		color = new int[N+1][N+1];
		chess = new Chess[K+1];
		map = new ArrayList[N+1][N+1];
		
		for (int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 1; j <= N; j++) {
				color[i][j] = Integer.parseInt(st.nextToken());
				map[i][j] = new ArrayList<>();
			}
		}
		
		int y, x, dir;
		for (int num = 1; num <= K; num++) {
			st = new StringTokenizer(br.readLine());
			y = Integer.parseInt(st.nextToken());
			x = Integer.parseInt(st.nextToken());
			dir = Integer.parseInt(st.nextToken());
			chess[num] = new Chess(y,x,dir);
			map[y][x].add(num);
		}
		solution();
	}

	private static void solution() {
		int ans = 0;
		while (++ans <= 1000) {
			game();
			if (!iscontinue) break;
		}
		if(ans > 1000) System.out.println(-1); // 값이 1,000보다 크거나 절대로 게임이 종료되지 않는 경우
		else System.out.println(ans); // 게임이 종료되는 턴의 번호
	}

	private static void game() {
		for (int num = 1; num <= K && iscontinue; num++) {
			int y = chess[num].y;
			int x = chess[num].x;
			int dir = chess[num].dir;

			// find
			int idx=0;
			for (int i = 0; i < map[y][x].size(); i++) {
				if (map[y][x].get(i) == num) {
					idx = i;
					break;
				}
			}

			// 이동 and 바뀐 위치 저장
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (ny<1 || ny>N || nx<1 || nx>N || color[ny][nx] == BLUE) move_blue(y, x, num, idx, dir);
			else if (color[ny][nx] == RED) move_red(y, x, idx, dir);
			else move_white(y, x, idx, dir); // WHITE
		}
	}
	
	static void move_red(int y, int x, int idx, int dir) { //  A번 말과 위에 있는 모든 말의 순서를 반대로 바꿔서 이동
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		for (int i = map[y][x].size() - 1; i >= idx; i--) {
			int num = map[y][x].get(i);
			map[ny][nx].add(num); // 이동
			chess[num].y = ny; // 바뀐 위치 저장
	        chess[num].x = nx;
		}
		// 턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료
		if (map[ny][nx].size() >= 4) { iscontinue = false; return; }
		int tmp = map[y][x].size() - idx;
		while (tmp-- > 0) map[y][x].remove(map[y][x].size()-1); // 옮겼으므로
	}

	static void move_white(int y, int x, int idx, int dir) {  // A번 말과 위에 있는 모든 말 이동
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		for (int i = idx; i < map[y][x].size(); i++) {
			int num = map[y][x].get(i);
			map[ny][nx].add(num); // 이동
			chess[num].y = ny; // 바뀐 위치 저장
	        chess[num].x = nx;
		}
		// 턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료
		if (map[ny][nx].size() >= 4) {iscontinue = false; return;}
		int tmp = map[y][x].size() - idx;
		while (tmp-- > 0) map[y][x].remove(map[y][x].size()-1); // 옮겼으므로
	}

	static void move_blue(int y, int x, int num, int idx, int dir) {
		if (dir == 1 || dir == 3) dir++; else dir--; // 방향 change
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		chess[num].dir = dir;  // 바뀐 방향 저장
		if (ny<1 || ny>N || nx<1 || nx>N || color[ny][nx] == BLUE) return;
		else if (color[ny][nx] == RED) move_red(y, x,  idx, dir);
		else if (color[ny][nx] == WHITE) move_white(y, x, idx, dir);
	}
}