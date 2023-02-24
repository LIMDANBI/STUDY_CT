import java.io.*;
import java.util.*;

public class Solution {
	
	static BufferedReader br = null;

	static final int INF = 10001;
	static final int EMPTY = 0;
	
	static final int dh[] = {-1, 1, 0, 0};
	static final int dw[] = {0, 0, -1, 1};
	
	static StringBuilder sb = new StringBuilder();
	static int ans;
	static int N, W, H;
	static int[][] map;
	static boolean[][] visited;

	public static void main(String[] args) throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
	    for(int t=1; t<=T; t++){
	    	ans=INF; // init
	    	input();
	        solution(0);
	        if(ans == INF) ans = 0;
	        sb.append("#"+t+" "+ans+"\n");
	    }
	    System.out.println(sb.toString());
	}
	
	static void input() throws Exception {
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		W = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
		map = new int[H][W];
		
	    for(int i=0; i<H; i++){
	    	st = new StringTokenizer(br.readLine());
	        for(int j=0; j<W; j++) map[i][j] = Integer.parseInt(st.nextToken());
	    }
	}
	
	static void solution(int cnt){ // 최대한 많은 Core에 전원을 연결하였을 경우, 전선 길이의 합
	    if(cnt == N){
	        ans = Math.min(ans, get_remain_brick());
	        return ; 
	    }

	     // 배열 복사
	    int[][] copy_map = new int[H][W];
	    for(int i=0; i<H; i++){
	        for(int j=0; j<W; j++) copy_map[i][j] = map[i][j];
	    }

	    for(int w=0; w<W; w++){
	        for(int h=0; h<H; h++){
	            if(map[h][w] == EMPTY) continue;
	            break_brick(h, w); // 구슬 쏘기
	            drop_brick(); // 벽돌이 밑으로 떨어짐
	            solution(cnt+1);

	            // 배열 복구
	            for(int i=0; i<H; i++){
	                for(int j=0; j<W; j++) map[i][j] = copy_map[i][j];
	            }
	            break; // 가장 위에 있는 벽돌만 깰 수 있음
	        }
	    }
	}

	private static void break_brick(int h, int w) {
		
		ArrayDeque<int[]> q = new ArrayDeque<>();
	    visited = new boolean[H][W];
	    q.offer(new int[]{h, w});
	    visited[h][w] = true;

	    while(!q.isEmpty()){
	        h = q.peek()[0];
	        w = q.peek()[1];
	        q.poll();

	        int cnt = map[h][w];
	        map[h][w] = EMPTY; // 벽돌 깨기

	        for(int d=0; d<4; d++){
	            int nh = h, nw = w;
	            for(int k=1; k<cnt; k++){ // 벽돌에 적힌 숫자 = 제거되는 범위
	                nh+=dh[d]; nw+=dw[d];
	                if(nh<0 || nh>=H || nw<0 || nw>=W) break; // 범위를 벗어나는 경우
	                if(visited[nh][nw] || map[nh][nw] == EMPTY) continue; // 이미 방문한 경우, 벽돌이 없는 경우
	                visited[nh][nw] = true;
	                q.offer(new int[]{nh, nw});
	            }
	        }
	    }
	}

	private static void drop_brick() {
	    for(int w=0; w<W; w++){
	        ArrayDeque<Integer> q = new ArrayDeque<>();
	        for(int h=H-1; h>=0; h--){
	            if(map[h][w]>0) {
	                q.offer(map[h][w]);
	                map[h][w] = EMPTY;
	            }
	        }

	        int h = H-1;
	        while(!q.isEmpty()) map[h--][w] = q.poll();
	    }
	}

	private static int get_remain_brick() {
	    int res = 0;
	    for(int i=0; i<H; i++){
	        for(int j=0; j<W; j++) {
	            if(map[i][j]>0) res++;
	        }
	    } return res;
	}

}