import java.io.*;
import java.util.*;

public class Main {

    static final int[] dy = { -1, 1, 0, 0 };
    static final int[] dx = { 0, 0, -1, 1 };

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        int[][][] dist = new int[N][M][2];
        boolean[][] map = new boolean[N][M];

        for (int i = 0; i < N; i++) {
            String line = br.readLine();
            for (int j = 0; j < M; j++)
                map[i][j] = (line.charAt(j) == '0' ? false : true);
        }

        ArrayDeque<int[]> q = new ArrayDeque<>();
        q.offer(new int[] { 0, 0, 1 });
        dist[0][0][1] = 1;

        while (!q.isEmpty()) {
            int y = q.peek()[0];
            int x = q.peek()[1];
            int c = q.peek()[2];
            q.poll();

            if (y == N - 1 && x == M - 1) {
                System.out.println(dist[y][x][c]);
                return;
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (ny < 0 || ny >= N || nx < 0 || nx >= M || dist[ny][nx][c] > 0)
                    continue;
                if (map[ny][nx] && c == 1) { // wall
                    dist[ny][nx][0] = dist[y][x][1] + 1;
                    q.offer(new int[] { ny, nx, 0 });
                } else if (!map[ny][nx]) { // empty
                    dist[ny][nx][c] = dist[y][x][c] + 1;
                    q.offer(new int[] { ny, nx, c });
                }
            }
        }
        System.out.println(-1);
        br.close();
    }
}