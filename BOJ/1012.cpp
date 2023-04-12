#include <iostream>
#include <cstring>
#define MAX 51
using namespace std;

int N, M, K;
bool map[MAX][MAX], visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init()
{
    memset(map, false, sizeof(map));
    memset(visited, false, sizeof(visited));
}

void input()
{
    cin >> N >> M >> K;

    int y, x;
    while (K--)
    {
        cin >> y >> x;
        map[y][x] = true;
    }
}

int dfs(int y, int x)
{
    visited[y][x] = true;

    int res = 1;
    for (int d = 0; d < 4; d++)
    {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M)
            continue;
        if (!map[ny][nx] || visited[ny][nx])
            continue;
        res += dfs(ny, nx);
    }
    return res;
}

int solution()
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!visited[i][j] && map[i][j])
            {
                dfs(i, j);
                ans++;
            }
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        init();
        input();
        cout << solution() << "\n";
    }
}