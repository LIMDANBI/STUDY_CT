#include <iostream>
#include <queue>
#define MAX 101
using namespace std;

struct INFO
{
    int y, x, d, cnt = 0;
    bool operator<(const INFO &d) const // 연산자 재정의
    {
        return cnt > d.cnt;
    }
} source, dest;

int N, M;
bool map[MAX][MAX];
bool visited[MAX][MAX][4];
int dy[] = {0, 0, 1, -1}; // 동 서 남 북
int dx[] = {1, -1, 0, 0};

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    }
    cin >> source.y >> source.x >> source.d;
    cin >> dest.y >> dest.x >> dest.d;

    // index를 0부터 시작하기 위해
    source = {source.y - 1, source.x - 1, source.d - 1, 0};
    dest = {dest.y - 1, dest.x - 1, dest.d - 1, 0};
}

int solution() // 로봇을 원하는 위치로 이동시키고, 원하는 방향으로 바라보도록 하는데 최소 몇 번의 명령이 필요한지
{
    visited[source.y][source.x][source.d] = true;
    priority_queue<INFO> pq;
    pq.push(source);

    while (!pq.empty())
    {
        int y = pq.top().y;
        int x = pq.top().x;
        int d = pq.top().d;
        int cnt = pq.top().cnt;
        pq.pop();

        if (y == dest.y && x == dest.x && d == dest.d)
            return cnt;

        // 명령 1
        for (int k = 1; k <= 3; k++) // k = 1 or 2 or 3
        {
            bool possible = true;
            int ny = y, nx = x;
            for (int i = 0; i < k; i++)
            {
                ny += dy[d];
                nx += dx[d];
                if (ny < 0 || ny >= N || nx < 0 || nx >= M || map[ny][nx])
                    possible = false;
            }
            if (possible && !visited[ny][nx][d])
            {
                visited[ny][nx][d] = true;
                pq.push({ny, nx, d, cnt + 1});
            }
        }

        // 명령 2
        int nd[2];
        if (d < 2) // 동 서 -> 남 북
        {
            nd[0] = 2;
            nd[1] = 3;
        }
        else // 남 북 -> 동 서
        {
            nd[0] = 0;
            nd[1] = 1;
        }

        for (int i = 0; i < 2; i++)
        {
            if (visited[y][x][nd[i]]) // 이미 해당 (좌표, 위치)에서 시도했거나, 할 예정인 경우
                continue;
            visited[y][x][nd[i]] = true;
            pq.push({y, x, nd[i], cnt + 1});
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    cout << solution();
}