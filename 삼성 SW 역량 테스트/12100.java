import java.io.*;
import java.util.*;

public class Main {
	
	static int N, ans = 0;
	static int[] dir = new int[5];
	static int[][] init_map;
	static Deque<Integer> tmp = new ArrayDeque<>();
	
	public static void main(String[] args) throws Exception {
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		// input
		N = Integer.parseInt(br.readLine());
		init_map = new int[N][N];
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) init_map[i][j] = Integer.parseInt(st.nextToken());
		}
		
		// solution
		solution(0);
		
		// output
		System.out.println(ans);
	}

	private static void solution(int cnt) {
	    if(cnt == 5){ // 최대 5번 이동시켜서 얻을 수 있는 가장 큰 블록 출력
	        
	         // copy map
	    	int[][] map = new int[N][N];
	        for(int i=0; i<N; i++){
	            for(int j=0; j<N; j++) map[i][j] = init_map[i][j];
	        }

	        // move
	        for(int i=0; i<5; i++){
	            if(dir[i]==0) move_up(map);
	            else if(dir[i]==1) move_down(map);
	            else if(dir[i]==2) move_left(map);
	            else move_right(map);
	        }

	        // ans update
	        ans = Math.max(ans, get_max_val(map));
	        return;
	    }
	    for(int i=0; i<4; i++){
	        dir[cnt] = i; // 이동 방향 설정
	        solution(cnt+1);
	    }
	}

	private static void move_up(int[][] map) {
	    for(int c=0; c<N; c++){

	        tmp.clear();
	        for(int r=0; r<N; r++){
	            if(map[r][c]!=0) tmp.add(map[r][c]);
	            map[r][c] = 0;
	        }

	        int r=0;
	        while(!tmp.isEmpty()){
	        	int num = tmp.poll();
	            if(!tmp.isEmpty() && num == tmp.peek()){
	                map[r++][c] = num*2;
	                tmp.poll();
	            }
	            else map[r++][c] = num;
	        }
	    }
	}

	private static void move_down(int[][] map) {
	    for(int c=0; c<N; c++){

	        tmp.clear();
	        for(int r=N-1; r>=0; r--){
	            if(map[r][c]!=0) tmp.add(map[r][c]);
	            map[r][c] = 0;
	        }

	        int r=N-1;
	        while(!tmp.isEmpty()){
	        	int num = tmp.poll();
	            if(!tmp.isEmpty() && num == tmp.peek()){
	                map[r--][c] =  num*2;
	                tmp.poll();
	            }
	            else map[r--][c] = num;
	        }
	    }
	}

	private static void move_left(int[][] map) {
	    for(int r=0; r<N; r++){

	        tmp.clear();
	        for(int c=0; c<N; c++){
	            if(map[r][c]!=0) tmp.add(map[r][c]);
	            map[r][c] = 0;
	        }

	        int c=0;
	        while(!tmp.isEmpty()){
	        	int num = tmp.poll();
	        	if(!tmp.isEmpty() && num == tmp.peek()){
	                map[r][c++] = num*2;
	                tmp.poll();
	            }
	            else map[r][c++] = num;
	        }
	    }
	}

	private static void move_right(int[][] map) {
	    for(int r=0; r<N; r++){

	        tmp.clear();
	        for(int c=N-1; c>=0; c--){
	            if(map[r][c]!=0) tmp.add(map[r][c]);
	            map[r][c] = 0;
	        }

	        int c=N-1;
	        while(!tmp.isEmpty()){
	        	int num = tmp.poll();
	        	if(!tmp.isEmpty() && num == tmp.peek()){
	                map[r][c--] =  num*2;
	                tmp.poll();
	            }
	            else map[r][c--] = num;
	        }
	    }
	}

	private static int get_max_val(int[][] map) {
	    int res = 0;
	    for(int i=0; i<N; i++){
	        for(int j=0; j<N; j++) res = Math.max(res, map[i][j]);
	    } return res;
	}
}