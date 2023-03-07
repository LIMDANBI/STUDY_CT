import java.io.*;
import java.util.*;

public class Main {
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		final int dr[] = {0, 1, 0, -1}; // 우하좌상
		final int dc[] = {1, 0, -1, 0};
		
		int N = Integer.parseInt(br.readLine());
		boolean[][] issnake = new boolean[N+1][N+1], isapple = new boolean[N+1][N+1];
		
		int K = Integer.parseInt(br.readLine()); // 사과의 개수
		while(K-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			isapple[r][c] = true;
		}
		
		ArrayDeque<int[]> dirInfo = new ArrayDeque<>();
		int L = Integer.parseInt(br.readLine());
		while(L-- > 0) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int s = Integer.parseInt(st.nextToken());
			int c = st.nextToken().charAt(0)=='L'?-1:1;
			dirInfo.offer(new int[] {s, c});
		}
		
		int dir = 0; // 뱀은 처음에 오른쪽을 향함 
		ArrayDeque<int[]> snake = new ArrayDeque<>();
		snake.offer(new int[] {1,1}); // 시작할때 뱀은 맨위 맨좌측에 위치
		issnake[1][1] = true;
		
		int sec = 0;
		while(++sec > 0) { // 게임 start
			// 뱀은 몸길이를 늘려 머리를 다음칸에 위치
			int nr = snake.peek()[0]+dr[dir];
			int nc = snake.peek()[1]+dc[dir];
			
			if(nr<1 || nr>N || nc<1 || nc>N || issnake[nr][nc]) break; // 자기자신 or 벽에 부딪히는 경우
			
			if(isapple[nr][nc]) { // 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않음 
				issnake[nr][nc] = true;
				isapple[nr][nc] = false;
				snake.offerFirst(new int[] {nr,nc});
			}
			else { // 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워줌 
				issnake[nr][nc] = true;
				snake.offerFirst(new int[] {nr,nc});
				
				int tr = snake.peekLast()[0];
				int tc = snake.peekLast()[1];
				issnake[tr][tc] = false;
				snake.pollLast();
			}
			
			if(!dirInfo.isEmpty() && dirInfo.peek()[0] == sec) {
				dir = (dir+dirInfo.peek()[1]+4)%4;
				dirInfo.pollFirst();
			}
		}
		System.out.println(sec);
	}
}