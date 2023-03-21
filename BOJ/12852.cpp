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
    if (N == 1)
    {
        cout << 0 << "\n"
             << 1;
        return 0;
    }

    dp[1] = dp[2] = dp[3] = 1;
    for (int i = 4; i <= N; i++)
    {
        dp[i] = dp[i - 1] + 1;
        if (i % 3 == 0)
            dp[i] = min(dp[i], dp[i / 3] + 1);
        if (i % 2 == 0)
            dp[i] = min(dp[i], dp[i / 2] + 1);
    }
    cout << dp[N] << "\n";
    cout << N << " ";

    int before = N;
    int nextCnt = dp[N] - 1;
    for (int now = N - 1; now > 1 && nextCnt; now--) // 역추적 해가며 N을 1로 만드는 방법에 포함되어 있는 수를 출력
    {
        if ((before - now == 1 || (before / 2 == now && before % 2 == 0) || (before / 3 == now && before % 3 == 0)) && dp[now] == nextCnt)
        {
            nextCnt--;
            before = now;
            cout << now << " ";
        }
    }
    cout << 1;
}