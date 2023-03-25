#include <iostream>
#define MAX 10001
using namespace std;

int N, M;
int num[MAX];

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> num[i];
}

void solution()
{
    int l = 0, r = 0, sum = num[0], ans = 0;
    while (l <= r && r < N)
    {
        if (sum <= M || l == r)
        {
            if (sum == M)
                ans++;
            sum += num[++r];
        }
        else
            sum -= num[l++];
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