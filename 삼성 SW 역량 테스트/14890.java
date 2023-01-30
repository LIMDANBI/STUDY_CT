import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N, L;
	static int[][] map;

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		L = Integer.parseInt(st.nextToken());
		map = new int[N][N];
		
	    for(int i=0; i<N; i++){
	    	st = new StringTokenizer(br.readLine());
	        for(int j=0; j<N; j++) {
	        	map[i][j] = Integer.parseInt(st.nextToken());
	        }
	    }
	    solution();
	}

	private static void solution() {
	    int ans = 0;
	    
	    // row check
	    for(int r=0; r<N ; r++){
	        
	        int cnt=1;
	        boolean ismake = true;
	        for(int c=0; c+1<N; c++){
	            if(map[r][c] == map[r][c+1]) cnt++;
	            else if(map[r][c]-map[r][c+1] == 1){ // 높이가 낮아지는 경우
	                if(cnt >= 0) cnt = 1-L;
	                else{
	                    ismake = false;
	                    break;
	                }
	            }
	            else if(map[r][c]-map[r][c+1] == -1){ // 높이가 높아지는 경우
	                if(cnt >= L) cnt = 1;
	                else {
	                    ismake = false;
	                    break;
	                }  
	            }
	            else { // 높이 차가 1 이상인 경우
	                ismake = false;
	                break;
	            }
	        }
	        if(cnt>=0 && ismake) ans++;
	    }

	    // column check
	    for(int c=0; c<N ; c++){ 

	        int cnt=1;
	        boolean ismake = true;
	        for(int r=0; r+1<N; r++){
	            if(map[r][c] == map[r+1][c]) cnt++;
	            else if(map[r][c]-map[r+1][c] == 1){ // 높이가 낮아지는 경우
	                if(cnt >= 0) cnt = 1-L;
	                else{
	                    ismake = false;
	                    break;
	                }
	            }
	            else if(map[r][c]-map[r+1][c] == -1){ // 높이가 높아지는 경우
	                if(cnt >= L) cnt = 1;
	                else {
	                    ismake = false;
	                    break;
	                } 
	            }
	            else { // 높이 차가 1 이상인 경우
	                ismake = false;
	                break;
	            }
	        }
	        if(cnt>=0 && ismake) ans++;
	    }

	    System.out.println(ans);
	}
}