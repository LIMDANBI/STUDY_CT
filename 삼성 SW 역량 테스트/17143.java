import java.io.*;
import java.util.*;

public class Main {
	
	static BufferedReader br = null;
	
	static final int[] dr = {-1,1,0,0}; // 상 하 우 좌 
	static final int[] dc = {0,0,1,-1};
	static final int EMPTY = 0;
	
	static class Shark {
		int r, c, s, d, z;
		boolean isDead = false;

		public Shark(int r, int c, int s, int d, int z, boolean isDead) {
			this.r = r;
			this.c = c;
			this.s = s;
			this.d = d;
			this.z = z;
			this.isDead = isDead;
		}
	}
	
	static int R, C, M;
	static Shark[] shark;
	static int[][] num, moved_num;
	
	static void input() throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		num = new int[R][C];
		shark = new Shark[M+1];
		
		for(int i=1; i<=M; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()); r--;
			int c = Integer.parseInt(st.nextToken()); c--;
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken()); d--;
			int z = Integer.parseInt(st.nextToken());
			shark[i] = new Shark(r, c, s, d, z, false);
			num[r][c] = i;
		}
		
		br.close();
	}
	
	static int catch_shark(int col) {
		for(int row=0; row<R; row++) {
			if(num[row][col]!=EMPTY) {
				int n = num[row][col]; // 상어 번호 
				shark[n].isDead = true;
				num[row][col] = EMPTY;
				return shark[n].z; // 잡은 상어 크기 
			}
		} return 0; // 잡을 수 있는 상어가 없는 경우 
	}
	
	static void move_shark() {
		moved_num = new int[R][C]; // 이동 후 정보 저장 
		for(int i=1; i<=M; i++) {
			if(shark[i].isDead) continue; // 이미 잡은 상어인 경우 
			int r = shark[i].r;
			int c = shark[i].c;
			int s = shark[i].s;
			int d = shark[i].d;
			int z = shark[i].z;
			
			if(d<2) s%=(R*2-2); // 상하 이동
			else s%=(C*2-2); // 좌우 이동 	
			
			while(s-->0) { // 남은 만큼 이동 
				r+=dr[d]; c+=dc[d];
				if(r<0 || r>=R || c<0 || c>=C) {
					if(d==0 || d==2) d++; else d--; // 방향 change
					r+=dr[d]*2; c+=dc[d]*2; // 잘못 간 것 까지 돌려 놓음 
				}
			}
			
			// 바뀐 상어 정보 update
			shark[i].r = r;
			shark[i].c = c;
			shark[i].d = d;
			
			if(moved_num[r][c] == EMPTY) moved_num[r][c] = i;
			else { // 크기가 가장 큰 상어가 나머지 상어를 모두 잡아먹음 
				int before = moved_num[r][c];
				if(shark[before].z < z) {
					shark[before].isDead = true;
					moved_num[r][c] = i;
				}
				else shark[i].isDead = true;
			}
		}
		
		for(int r=0; r<R; r++) {
			for(int c=0; c<C; c++) num[r][c] = moved_num[r][c];
		}
	}
	
	static void solution() { // 낚시왕이 잡은 상어 크기의 합
		
		int ans = 0;
		for(int col=0; col<C; col++) { // 낚시왕이 오른쪽으로 한 칸 이동
			
			// 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡음 
			ans+=catch_shark(col);
			
			// 상어가 이동
			move_shark();
		}
		System.out.println(ans);
	}

	public static void main(String[] args) throws Exception {
		input();
		solution();
	}
}