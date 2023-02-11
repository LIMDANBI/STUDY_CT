import java.io.*;
import java.util.*;

public class Solution {
	
	static final int dy[] = {-1, 1, 0, 0};
	static final int dx[] = {0, 0, -1, 1};
	
	static StringBuilder sb = new StringBuilder();
	static int N, connected, ans;
	static List<int[]> cores;
	static boolean[][] map;

	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		int T = Integer.parseInt(br.readLine());
	    for(int t=1; t<=T; t++){
	        
	    	// init
	    	ans = Integer.MAX_VALUE;
	    	connected = 0;
	    	cores = new ArrayList<>();
	    	
	    	// input
	    	N = Integer.parseInt(br.readLine());
	    	map = new boolean[N][N];
	        for(int y=0; y<N; y++){
	        	st = new StringTokenizer(br.readLine());
	            for(int x=0; x<N; x++){
	                map[y][x] = (Integer.parseInt(st.nextToken())==1?true:false);
	                if(map[y][x]) {
	                    if(y!=0 && y!=N-1 && x!=0 && x!=N-1) cores.add(new int[]{y, x});
	                    else connected++; // 이미 전원이 연결된 것
	                }
	            }
	        }
	        solution(0, connected, 0);
	        sb.append("#"+t+" "+ans+"\n");
	    }
	    System.out.println(sb.toString());
	}
	
	static void solution(int idx, int conn, int sum){ // 최대한 많은 Core에 전원을 연결하였을 경우, 전선 길이의 합
	    
	    if(connected <= conn){ // 최대한 많은 Core에 전원을 연결
	        if(connected == conn) ans = Math.min(ans, sum); // 여러 방법이 있을 경우, 전선 길이의 합이 최소가 되는 값
	        else {
	            ans = sum;
	            connected = conn;
	        }
	    }

	    if(idx>=cores.size()) return; // end

	    int y = cores.get(idx)[0]; // idx번째 core 선택
	    int x = cores.get(idx)[1];

	    for(int d=0; d<4; d++){ // 4가지 방향 (전선은 직선으로만 설치가 가능)

	        int len=0, ny=y, nx=x;

	        while(true){
	            ny+=dy[d]; nx+=dx[d]; len++;
	            if(ny<0 || ny>=N || nx<0 || nx>=N) break; // 범위를 벗어나는 경우 
	            if(map[ny][nx]) {len = 0; break;} // 설치가 불가능한 경우
	        }

	        if(len == 0) continue; // 불가능한 경우

	        ny=y; nx=x; len--;
	        for(int i=0; i<len; i++){ // 전선 설치
	            ny+=dy[d]; nx+=dx[d];
	            map[ny][nx] = true;
	        }

	        solution(idx+1, conn+1, sum+len);

	        for(int i=0; i<len; i++){ // 전선 해제
	            map[ny][nx] = false;
	            ny-=dy[d]; nx-=dx[d];
	        }
	    }

	    solution(idx+1, conn, sum); // idx번째 core 미선택 
	}
}