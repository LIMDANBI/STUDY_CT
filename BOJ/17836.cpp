#include <iostream>
#include <queue>
#define MAX 101
using namespace std;

struct DATA
{
    int y, x, isgram;
};

int N, M, T;
int map[MAX][MAX];
int cost[MAX][MAX][2];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input()
{
    cin >> N >> M >> T;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    }
}

int solution()
{
    queue<DATA> q;
    q.push({0, 0, 0});
    cost[0][0][0] = 1;

    while (!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int isgram = q.front().isgram;
        q.pop();

        if (y == N - 1 && x == M - 1)
        {
            if (cost[y][x][isgram] - 1 <= T)
                return cost[y][x][isgram] - 1;
        }

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= M || cost[ny][nx][isgram]) // 범위를 벗어나는 경우, 이미 방문한 경우
                continue;
            if (isgram) // 그람을 가지고 있는 경우
            {
                cost[ny][nx][isgram] = cost[y][x][isgram] + 1;
                q.push({ny, nx, isgram});
            }
            else // 그람이 없는 경우
            {
                if (map[ny][nx] == 2) // 그람을 획득하는 경우
                {
                    cost[ny][nx][1] = cost[y][x][0] + 1;
                    q.push({ny, nx, 1});
                }
                else if (map[ny][nx] != 1) // 벽이 아닌 경우
                {
                    cost[ny][nx][isgram] = cost[y][x][isgram] + 1;
                    q.push({ny, nx, 0});
                }
            }
        }
    }
    return -1; // T 시간 이내에 공주에게 도달할 수 없는 경우
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    int res = solution();
    res == -1 ? cout << "Fail" : cout << res;
}