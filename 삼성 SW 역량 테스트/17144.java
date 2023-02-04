import java.io.*;
import java.util.*;

public class Main {
	
	static int ar = 0;
	static int R, C, T;;
	static int home[][], copy_home[][];
	static int dr[] = {-1, 1, 0, 0};
	static int dc[] = {0, 0, -1, 1};
	
	public static void main(String[] args) throws Exception {
		
		// System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		home = new int[R][C];
		copy_home = new int[R][C];
		
		for(int i=0; i<R; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<C; j++) {
				home[i][j] = Integer.parseInt(st.nextToken());
	            if(home[i][j] == -1){
	                home[i][j] = 0;
	                if(ar==0) ar = i; // 공기 청정기의 위치
	            }
			}
		}
	    while(T-- > 0){
	        dust(); // 미세먼지가 확산
	        clean(); // 공기청정기가 작동
	    }
	    output();
	}

	private static void dust() {
	    int r, c, div;
	    for(int i=0; i<R; i++){
	        for(int j=0; j<C; j++){
	            if(home[i][j] == 0) continue; // 먼지가 없거나, 공기청정기인 경우
	            div = home[i][j]/5;
	            for(int d=0; d<4; d++){
	                r = i+dr[d];
	                c = j+dc[d];
	                if(r<0 || r>=R || c<0 || c>=C) continue; // 범위를 벗어나는 경우
	                if((r==ar || r==ar+1) && c==0) continue; // 공기청정기 위치인 경우
	                copy_home[r][c] += div;
	                copy_home[i][j] -= div;
	            }
	        }
	    }

	    for(int i=0; i<R; i++){
	        for(int j=0; j<C; j++){
	            home[i][j] += copy_home[i][j];
	            copy_home[i][j] = 0;
	        }
	    }
	}

	private static void clean() {
	    // 위쪽 순환
	    for(int i=ar-1; i>0; i--) home[i][0] = home[i-1][0]; // 하
	    for(int i=0; i<C-1; i++) home[0][i] = home[0][i+1]; // 좌
	    for(int i=0; i<ar; i++) home[i][C-1] = home[i+1][C-1]; // 상
	    for(int i=C-1; i>0; i--) home[ar][i] = home[ar][i-1]; // 우

	    // 아래쪽 순환
	    for(int i=ar+2; i<R-1; i++) home[i][0] = home[i+1][0]; // 상
	    for(int i=0; i<C-1; i++) home[R-1][i] = home[R-1][i+1]; // 좌
	    for(int i=R-1; i>ar+1; i--) home[i][C-1] = home[i-1][C-1]; // 하
	    for(int i=C-1; i>0; i--) home[ar+1][i] = home[ar+1][i-1]; // 우
	}

	private static void output() {
	    int ans = 0;
	    for(int i=0; i<R; i++){
	        for(int j=0; j<C; j++) ans+=home[i][j];
	    }
	    System.out.println(ans);
	}

}