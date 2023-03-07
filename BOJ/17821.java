import java.io.*;
import java.util.*;

public class Main {
	
	static final int PLAYER=9, OUT=0;
	
	static int N;
	static int ans=0;
	static boolean[] v;
	static int[] order;
	static int[][] round;
	
	static int get_play_result() {
		int res = 0;
		
		int idx=0, player; // 이닝이 변경되어도 타순 유지
		ArrayDeque<Integer> tmp, runners;
		for(int inning=0; inning<N; inning++) {
			int out=0, hitCnt;
			tmp = new ArrayDeque<>();
			runners = new ArrayDeque<>();
			
			while(true) {
				player = order[idx]; 
				idx = (idx+1)%PLAYER;
				if(round[inning][player] == OUT) { if(++out==3) break;}
				else { // 
					hitCnt = round[inning][player];
					runners.offer(0);
					while(!runners.isEmpty()) {
						int now = runners.poll();
						if(now+hitCnt > 3) res++;
						else tmp.offer(now+hitCnt);
					}
					while(!tmp.isEmpty()) runners.offer(tmp.poll());
				}
			}
		}
		return res;
	}
	
	static void set_order(int cnt) {
		if(cnt == PLAYER) { // player 순서를 모두 정한 경우
			ans = Math.max(ans, get_play_result());
			return ;
		}
		for(int p=1; p<PLAYER; p++) {
			if(v[p]) continue;
			v[p] = true;
			order[cnt] = p;
			if(cnt==2) set_order(cnt+2);
			else set_order(cnt+1);
			v[p] = false;
		}
	}

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		order = new int[PLAYER];
		round = new int[N][PLAYER];
		v = new boolean[PLAYER];
		
		for(int n=0; n<N; n++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for(int p=0; p<PLAYER; p++) round[n][p] = Integer.parseInt(st.nextToken());
		}
		
		v[0] = true; order[3] = 0; // 1번 선수를 4번 타자로 미리 결정 (idx start with 0)
		set_order(0); // 나머지 선수들의 타순을 정함
		System.out.println(ans);
	}
}