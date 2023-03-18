#include <iostream>
#include <vector>
#define MAX 1500001
using namespace std;

struct DATA
{
    int t, p;
};

int N;
int dp[MAX];
vector<DATA> v;

void input()
{
    cin >> N;
    int t, p;
    for (int i = 0; i < N; i++)
    {
        cin >> t >> p;
        v.push_back({t, p});
    }
}

void solution()
{
    for (int day = N - 1; day >= 0; day--)
    {
        int p = v[day].p;
        int t = v[day].t;
        if (day + t > N)
            dp[day] = dp[day + 1];
        else
            dp[day] = max(dp[day + 1], dp[day + t] + p);
    }
    cout << dp[0];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}