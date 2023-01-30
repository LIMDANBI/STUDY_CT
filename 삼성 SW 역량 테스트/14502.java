import java.io.*;
import java.util.*;

public class Main {
	
	static final int EMPTY = 0;
	static final int WALL = 1;
	static final int VIRUS = 2;
	
    static int N, M, ans = 0;
    static int[][] lab, copy_lab;
    static final int[] dy = { -1,1,0,0 };
    static final int[] dx = { 0,0,-1,1 };
    
    static List<int[]> virus = new ArrayList<>();
    
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        lab = new int[N][M];
        copy_lab = new int[N][M];
        
        for(int i=0; i<N; i++) {
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<M; j++) {
            	lab[i][j] = Integer.parseInt(st.nextToken());
            	if(lab[i][j] == VIRUS) virus.add(new int[]{i, j});
            }
        }
        solution(0);
        System.out.println(ans);
    }
	
    private static void spread_virus(int y, int x) {
        copy_lab[y][x] = VIRUS;
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
            if (copy_lab[ny][nx] != EMPTY) continue;
            spread_virus(ny, nx);
        }
    }
	
    public static void solution(int cnt) {
        if (cnt == 3) {

            // 1. copy map
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) copy_lab[i][j] = lab[i][j];
            }

            // 2. spread_virus
            for (int i = 0; i < virus.size(); i++) {
                spread_virus(virus.get(i)[0], virus.get(i)[1]);
            }

            // 3. get max safety zone
            int res = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if(copy_lab[i][j] == EMPTY) res++;
                }
            }

            // 4. update ans;
            ans = Math.max(ans, res);
            return;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (lab[i][j] != EMPTY) continue;
                lab[i][j] = WALL;
                solution(cnt + 1);
                lab[i][j] = EMPTY;
            }
        }
    }
}