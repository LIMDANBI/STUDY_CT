#include <iostream>
#include <algorithm>
#define MAX 15001
using namespace std;

int N, M;
int arr[MAX];

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> arr[i];
}

void solution()
{
    sort(arr, arr + N);

    int l = 0, r = N - 1, ans = 0;
    while (l < r)
    {
        if (arr[l] + arr[r] == M)
        {
            ans++;
            l++;
            r--;
        }
        else if (arr[l] + arr[r] < M)
            l++;
        else
            r--;
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