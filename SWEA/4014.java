import java.io.*;
import java.util.*;

public class Solution {
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("res/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		int T = Integer.parseInt(br.readLine());
		for(int t=1; t<=T; t++) {
			
			StringTokenizer st = new StringTokenizer(br.readLine());
			int N = Integer.parseInt(st.nextToken());
			int X = Integer.parseInt(st.nextToken());
			int[][] map = new int[N][N];
			
			for(int i=0; i<N; i++) {
				st = new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<N; j++)
					map[i][j] = Integer.parseInt(st.nextToken());
			}
			
			int ans = 0; // 활주로를 건설할 수 있는 경우의 수
			
			// row 체크
			for(int c=0; c<N; c++) {
				boolean possible = true;
				int before=map[0][c], cnt=0;
				for(int r=0; r<N; r++) {
					if(map[r][c] == before) cnt++;
					else {
						int diff = Math.abs(map[r][c]-before);
						if(diff!=1 || cnt<0) possible = false;
						if(before < map[r][c]) {
							if(cnt<X) possible = false;
							else cnt=1;
						}
						else cnt = -X+1;// before > now
						before = map[r][c];
					}
				}
				if(cnt < 0) possible = false;
				if(possible) ans++;
			}
			
			// column 체크
			for(int r=0; r<N; r++) {
				boolean possible = true;
				int before=map[r][0], cnt=0;
				for(int c=0; c<N; c++) {
					if(map[r][c] == before) cnt++;
					else {
						int diff = Math.abs(map[r][c]-before);
						if(diff!=1 || cnt<0) possible = false;
						if(before < map[r][c]) {
							if(cnt<X) possible = false;
							else cnt=1;
						}
						else cnt = -X+1;// before > now
						before = map[r][c];
					}
				}
				if(cnt < 0) possible = false;
				if(possible) ans++;
			}
			sb.append("#" + t + " " + ans + "\n");
		}
		System.out.println(sb.toString());
		br.close();
	}
}