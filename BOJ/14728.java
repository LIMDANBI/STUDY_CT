import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int T = Integer.parseInt(st.nextToken());
        int[][] dp = new int[N + 1][T + 1];
        int[] K = new int[N + 1], S = new int[N + 1];

        for (int i = 1; i <= N; i++) {
            st = new StringTokenizer(br.readLine());
            K[i] = Integer.parseInt(st.nextToken());
            S[i] = Integer.parseInt(st.nextToken());
        }

        for (int n = 1; n <= N; n++) {
            for (int t = 1; t <= T; t++) {
                if (t < K[n])
                    dp[n][t] = dp[n - 1][t];
                else
                    dp[n][t] = Math.max(dp[n - 1][t], dp[n - 1][t - K[n]] + S[n]);
            }
        }
        System.out.println(dp[N][T]);
    }
}