#include <iostream>
#define MAX 10001
using namespace std;

int N, M;
int max_budget;
int budget[MAX];

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> budget[i];
        max_budget = max(budget[i], max_budget);
    }
    cin >> M;
}

bool check(int val)
{
    int res = 0;
    for (int i = 0; i < N; i++)
        res += min(val, budget[i]);

    if (res <= M)
        return true;
    return false;
}

void solution()
{
    int low = 0, mid, high = max_budget;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (check(mid))
            low = mid + 1;
        else
            high = mid - 1;
    }
    cout << high;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}