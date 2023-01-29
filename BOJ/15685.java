import java.io.*;
import java.util.*;

public class Main {
	
	private static boolean[][] map = new boolean[101][101];
	private static int dy[] = {0, -1, 0, 1};
	private static int dx[] = {1, 0, -1, 0};
	private static int N;

	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		N = Integer.parseInt(br.readLine());
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int g = Integer.parseInt(st.nextToken());
			solution(x, y, d, g);
		}
		output();
	}
	
	public static void solution(int x, int y, int d, int g) {
	    List<Integer> dir = new ArrayList<>();

	    // 0 세대 드래콘 커브
	    map[y][x] = true;
	    y+=dy[d]; x+=dx[d];
	    map[y][x] = true;
	    dir.add(d);

	    while(g-- > 0){ // g세대 드래곤 커브를 만듦
	        for(int i=dir.size()-1; i>=0; i--){ // 거꾸로
	            int nd = (dir.get(i)+1)%4;
	            y+=dy[nd]; x+=dx[nd];
	            map[y][x] = true;
	            dir.add(nd);
	        }
	    }
	}
	
	public static void output() {
		int ans = 0;
	    for(int i=0; i<100; i++){
	        for(int j=0; j<100; j++){
	            if(map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1]) ans++;
	        }
	    } System.out.println(ans);
	}
}
