import java.io.*;
import java.util.*;

public class Main {
	
	private static int dy[] = {0, -1, 0, 1};
	private static int dx[] = {1, 0, -1, 0};
	private static int N, L, R, total;
	
	private static int[][] map;
	private static boolean[][] visited;
	static List<int[]> pos = new ArrayList<int[]>();

	public static void main(String[] args) throws Exception {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		L = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		
		map = new int[N][N];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		solution();
	}

	private static void solution() {
	    int ans = 0;
	    while(true){
	        
	        visited = new boolean[N][N];
	        
	        boolean ismove = false;
	        for(int i=0; i<N; i++){
	            for(int j=0; j<N; j++){
	                if(visited[i][j]) continue;
	                pos = new ArrayList<int[]>();
	                total = map[i][j];
	                make_union(i, j); // 연합을 이루고

	                if(pos.size() == 1) continue;
	                
	                // 인구 이동
	                ismove = true;
	                int avg = total/(int)pos.size();
	                for(int p=0; p<(int)pos.size(); p++){
	                    int y = pos.get(p)[0];
	                    int x = pos.get(p)[1];
	                    map[y][x] = avg;
	                }
	            }
	        }
	        if(!ismove) break; // 인구 이동이 발생하지 않는 경우
	        ans++; // 인구 이동이 발생한 경우
	    } 
	    System.out.println(ans);
	}

	private static void make_union(int y, int x){
	    visited[y][x] = true;
	    pos.add(new int[] {y,x});

	    for(int d=0; d<4; d++){
	        int ny = y+dy[d];
	        int nx = x+dx[d];
	        if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
	        int diff = Math.abs(map[y][x]-map[ny][nx]); // 국경선을 공유하는 두 나라의 인구 차
	        if(L<=diff && diff<=R){ // L명 이상, R명 이하인 경우
	            total+=map[ny][nx];
	            make_union(ny, nx);
	        }
	    }
	}
}