#include <iostream>
#define MAX 250001
using namespace std;

int N, X;
int num[MAX];

void input()
{
    cin >> N >> X;
    for (int i = 0; i < N; i++)
        cin >> num[i];
}

void solution()
{
    int visitor = 0, cnt = 0, max_visitor = 0;

    for (int i = 0; i < X; i++)
        visitor += num[i];
    max_visitor = visitor;
    cnt = 1;

    for (int i = X; i <= N; i++)
    {
        visitor -= num[i - X];
        visitor += num[i];

        if (visitor == max_visitor)
            cnt++;
        if (max_visitor < visitor)
        {
            max_visitor = visitor;
            cnt = 1;
        }
    }

    if (max_visitor == 0)
        cout << "SAD";
    else
    {
        cout << max_visitor << "\n"
             << cnt;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}