import java.io.*;
import java.util.*;

public class Solution {

    static BufferedReader br = null;

    static final int[] dy = {-1,1,0,0};
    static final int[] dx = {0,0,-1,1};
    static final int EMPTY=0;

    static boolean[][] visited;
    static PriorityQueue<int[]> pq;
    static int N, M, K, size_N, size_M, start;

    static void input() throws Exception{
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        start = K/2+1;
        size_N = N+K+1;
        size_M = M+K+1;
        visited = new boolean[size_N][size_M];
        pq = new PriorityQueue<int[]>((o1, o2)->Integer.compare(o2[2], o1[2]));

        for(int i=0; i<N; i++) {
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<M; j++) {
                int x = Integer.parseInt(st.nextToken());
                if(x != EMPTY) {
                    visited[i+start][j+start] = true;
                    pq.offer(new int[] {i+start, j+start, x, x}); // pos(y,x) vitality current
            	}
            }
        }
    }

    static void cell_culture() {
        ArrayDeque<int[]> q = new ArrayDeque<>();

        while(K-->0) {
            int ny, nx;
            while(!pq.isEmpty()) {
                int[] cell = pq.poll();
                cell[3]--;

                if(cell[3] < 0) {
                    for(int d=0; d<4; d++) {
                        ny = cell[0] + dy[d];
                        nx = cell[1] + dx[d];
                        if(visited[ny][nx]) continue; // 빈 공간이 아닌 경우
                        visited[ny][nx] = true;
                        q.offer(new int[] {ny,nx, cell[2], cell[2]}); // 번식된 세포
                    }
                }
                if(cell[2]+cell[3] == 0) continue; // dead		
                q.offer(cell);
            }
            while(!q.isEmpty()) pq.offer(q.poll());
        }
    }


    public static void main(String[] args) throws Exception {
        StringBuilder sb = new StringBuilder();
        br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        for(int t=1; t<=T; t++) {
            input();
            cell_culture();
            sb.append("#"+t+" "+pq.size()+"\n");
        }
        System.out.println(sb.toString());
    }
}