import java.io.*;
import java.util.*;

public class Main {
	
	static int N, M, K;
	static int[][] arr;
	static int[][] cycle;
	static boolean[] visited;
	static int ans = Integer.MAX_VALUE;

	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		arr = new int[N][M];
		cycle = new int[K][3];
		visited = new boolean[K];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
	
		for(int k=0; k<K; k++) {
			st = new StringTokenizer(br.readLine());
			cycle[k][0] = Integer.parseInt(st.nextToken())-1;
			cycle[k][1] = Integer.parseInt(st.nextToken())-1;
			cycle[k][2] = Integer.parseInt(st.nextToken());
		}
		
		solution(0);
		sb.append(ans);
		System.out.println(sb.toString());
		br.close();
	}
	
	public static int get_min_val() {
		int res = Integer.MAX_VALUE;
		for(int i=0; i<N; i++) {
			int sum = 0;
			for(int j=0; j<M; j++) sum+=arr[i][j];
			res = Math.min(res, sum);
		}
		return res;
	}
	
	public static void roate_arr(int r, int c, int s) {
        int ur = r-s, uc = c-s; // 좌측 상단 좌표
	    int dr = r+s, dc = c+s; // 우측 하단 좌표

	    while(true){
	        if(ur >= dr) break; // 종료 조건
	        int tmp = arr[ur][uc];
	        for(int i=ur; i<dr; i++) arr[i][uc] = arr[i+1][uc]; // 좌
	        for(int j=uc; j<dc; j++) arr[dr][j] = arr[dr][j+1]; // 하
	        for(int i=dr; i>ur; i--) arr[i][dc] = arr[i-1][dc]; // 우
	        for(int j=dc; j>uc; j--) arr[ur][j] = arr[ur][j-1]; // 상
	        arr[ur][uc+1] = tmp;
	        ur++; uc++;
	        dr--; dc--;
	    }
	}
	
	public static void solution(int cnt) {
		if(cnt == K) {
			ans = Math.min(ans,  get_min_val());
			return ;
		}
		
		for(int k=0; k<K; k++) {
			if(visited[k]) continue; // 이미 사용한 경우
			visited[k] = true; // 사용
			
			// save state
            int[][] copy_arr = new int[N][M];
	        for(int i=0; i<N; i++){
	            for(int j=0; j<M; j++) copy_arr[i][j] = arr[i][j];
	        }
	        
            roate_arr(cycle[k][0], cycle[k][1], cycle[k][2]); // 회전 연산
            solution(cnt+1); // 순열 구현

            visited[k] = false; // 다른 순열에서 사용하기 위해
			
			// recovery
	        for(int i=0; i<N; i++){
	            for(int j=0; j<M; j++) arr[i][j] = copy_arr[i][j];
            } 
        }
	}
}