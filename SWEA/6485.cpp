#include <iostream>
#include <cstring>
#define MAX 5001
using namespace std;

int N, P;
int cnt[MAX];

int solution(int t)
{
    cin >> N;
    while (N--)
    {
        int a, b;
        cin >> a >> b;
        for (int i = a; i <= b; i++)
            cnt[i]++;
    }
    cin >> P;

    cout << "#" << t << " ";
    while (P--)
    {
        int n;
        cin >> n;
        cout << cnt[n] << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        memset(cnt, 0, sizeof(cnt));
        solution(t);
    }
}