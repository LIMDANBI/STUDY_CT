#include <iostream>
#include <queue>
#include <set>
#define MAX 1001
using namespace std;

int N, M;
int inDegree[MAX];
set<int> list[MAX];

void input()
{
    cin >> N >> M;

    int singerNum, num;
    for (int i = 0; i < M; i++)
    {
        cin >> singerNum;
        int a, b;
        cin >> a;
        while (--singerNum)
        {
            cin >> b;
            if (list[a].find(b) == list[a].end())
                inDegree[b]++;
            list[a].insert(b);
            a = b;
        }
    }
}

void solution()
{
    queue<int> q, ans;
    for (int i = 1; i <= N; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
            ans.push(i);
        }
    }

    while (!q.empty())
    {
        int n = q.front();
        q.pop();
        for (auto next : list[n])
        {
            if (--inDegree[next] == 0)
            {
                q.push(next);
                ans.push(next);
            }
        }
    }

    if (ans.size() != N)
        cout << 0;
    else
    {
        while (!ans.empty())
        {
            cout << ans.front() << "\n";
            ans.pop();
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}