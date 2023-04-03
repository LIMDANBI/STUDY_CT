import java.io.*;
import java.util.*;

public class Solution {

    static int K;
    static boolean[][] sPole;

    private static void roataion(int n, int d, int path) {

        boolean before = sPole[n][6], next = sPole[n][2];

        if (d == 1) { // 시계방향
            boolean tmp = sPole[n][7];
            for (int i = 7; i > 0; i--)
                sPole[n][i] = sPole[n][i - 1];
            sPole[n][0] = tmp;
        } else { // 반시계방향
            boolean tmp = sPole[n][0];
            for (int i = 0; i < 7; i++)
                sPole[n][i] = sPole[n][i + 1];
            sPole[n][7] = tmp;
        }

        // 서로 붙어 있는 날의 자성과 다를 경우, 반대 방향으로 한칸 회전
        if (n - 1 >= 0 && before != sPole[n - 1][2] && path <= 0)
            roataion(n - 1, -d, -1);
        if (n + 1 < 4 && next != sPole[n + 1][6] && path >= 0)
            roataion(n + 1, -d, 1);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        StringTokenizer st = null;

        int T = Integer.parseInt(br.readLine());
        for (int t = 1; t <= T; t++) {
            K = Integer.parseInt(br.readLine());
            sPole = new boolean[4][8];

            for (int i = 0; i < 4; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j = 0; j < 8; j++)
                    sPole[i][j] = (Integer.parseInt(st.nextToken()) == 0 ? false : true);
            }

            for (int k = 0; k < K; k++) {
                st = new StringTokenizer(br.readLine());
                int n = Integer.parseInt(st.nextToken()) - 1;
                int d = Integer.parseInt(st.nextToken());
                roataion(n, d, 0);
            }

            int ans = 0;
            int[] pow = { 1, 2, 4, 8 };
            for (int i = 0; i < 4; i++) {
                if (sPole[i][0])
                    ans += pow[i]; // N극인 경우
            }
            sb.append("#" + t + " " + ans + "\n");
        }

        System.out.println(sb.toString());
        br.close();
    }
}