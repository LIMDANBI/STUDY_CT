#include <iostream>
#define MAX 1000001
using namespace std;

int N;
int dp[MAX];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;

    dp[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        dp[i] = dp[i - 1] + 1;
        if (i % 2 == 0 && dp[i / 2] + 1 < dp[i])
            dp[i] = dp[i / 2] + 1;

        if (i % 3 == 0 && dp[i / 3] + 1 < dp[i])
            dp[i] = dp[i / 3] + 1;
    }
    cout << dp[N] << "\n";

    int nextCnt = dp[N] - 1;
    while (N != 0)
    {
        cout << N << " ";
        if (N % 3 == 0 && dp[N / 3] == nextCnt)
            N /= 3;
        else if (N % 2 == 0 && dp[N / 2] == nextCnt)
            N /= 2;

        else
            N--;
        nextCnt--;
    }
}