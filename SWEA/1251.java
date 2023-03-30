import java.io.*;
import java.util.*;

public class Solution {

    static BufferedReader br = null;
    static int N;
    static double E;
    static int[] parent;
    static int[][] island;

    static class Edge {
        long len;
        int a, b;

        public Edge(long len, int a, int b) {
            this.len = len;
            this.a = a;
            this.b = b;
        }
    }

    private static void input() throws Exception {
        StringTokenizer st = null;
        N = Integer.parseInt(br.readLine());
        parent = new int[N];
        island = new int[N][2];

        // x 좌표
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++)
            island[i][0] = Integer.parseInt(st.nextToken(" "));

        // y 좌표
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            island[i][1] = Integer.parseInt(st.nextToken(" "));
        }

        E = Double.parseDouble(br.readLine());
    }

    private static PriorityQueue<Edge> get_dist() {
        PriorityQueue<Edge> res = new PriorityQueue<>((o1, o2) -> Long.compare(o1.len, o2.len)); // cost a b
        for (int a = 0; a < N - 1; a++) {
            for (int b = a + 1; b < N; b++) {
                long l = (long) (Math.pow(island[a][0] - island[b][0], 2) + Math.pow(island[a][1] - island[b][1], 2));
                res.add(new Edge(l, a, b));
            }
        }
        return res;
    }

    private static int Find(int x) {
        if (x == parent[x])
            return x;
        return parent[x] = Find(parent[x]); // 경로 단축
    }

    private static void Union(int x, int y) { // x 밑에 y를 연결
        parent[Find(y)] = Find(x);
    }

    private static long solution() {

        // init
        for (int i = 0; i < N; i++)
            parent[i] = i;

        // get dist
        PriorityQueue<Edge> pq = get_dist();

        int connected = 0;
        double totalCost = 0;

        while (connected != N - 1) {
            int a = pq.peek().a;
            int b = pq.peek().b;
            long l = pq.peek().len;
            pq.poll();

            if (Find(a) != Find(b)) {// 연결되지 않은 경우
                Union(a, b);
                connected++;
                totalCost += (E * l);
            }
        }
        return Math.round(totalCost);
    }

    public static void main(String[] args) throws Exception {
        StringBuilder sb = new StringBuilder();
        br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        for (int t = 1; t <= T; t++) {
            input();
            sb.append("#" + t + " " + solution() + "\n");
        }
        System.out.println(sb.toString());
    }
}