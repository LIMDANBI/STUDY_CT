#include <iostream>
#include <vector>
#include <queue>
#define MAX 32001
using namespace std;

int N, M;
int inDegree[MAX];
vector<int> order[MAX];

void input()
{
    cin >> N >> M;

    int a, b;
    while (M--)
    {
        cin >> a >> b;
        order[a].push_back(b);
        inDegree[b]++;
    }
}

void solution()
{ // 먼저 푸는 것이 좋은 경우 반드시 먼저 품, 가능한 쉬운 문제 부터
    priority_queue<int> pq;
    for (int i = 1; i <= N; i++)
    {
        if (inDegree[i] == 0)
            pq.push(-i); // min heap
    }

    while (!pq.empty())
    {
        int num = -pq.top();
        cout << num << " ";
        pq.pop();

        for (int i = 0; i < order[num].size(); i++)
        {
            if (--inDegree[order[num][i]] == 0)
                pq.push(-order[num][i]);
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