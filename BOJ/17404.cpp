#include <iostream>
#define MAX 1002
using namespace std;

int N;
int cost[MAX][3], dp[MAX][3];

void input()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> cost[i][j];
    }
}

void init()
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j < 3; j++)
            dp[i][j] = MAX;
    }
}

void solution() // 모든 집을 칠하는 비용의 최솟값
{
    int ans = MAX * MAX;
    for (int c = 0; c < 3; c++)
    {
        // init
        init();

        // dp
        dp[1][c] = cost[1][c]; // 1번 집의 색상을 고정
        for (int r = 2; r <= N; r++)
        {
            dp[r][0] = min(dp[r - 1][1], dp[r - 1][2]) + cost[r][0];
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]) + cost[r][1];
            dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]) + cost[r][2];
        }

        // ans update
        if (c == 0)
            ans = min(ans, min(dp[N][1], dp[N][2]));
        else if (c == 1)
            ans = min(ans, min(dp[N][0], dp[N][2]));
        else if (c == 2)
            ans = min(ans, min(dp[N][0], dp[N][1]));
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}