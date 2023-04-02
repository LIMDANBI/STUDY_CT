#include <iostream>
#define MAX 251
using namespace std;

int R, C;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        string line;
        cin >> line;
        for (int j = 0; j < C; j++)
        {
            map[i][j] = line[j];
        }
    }
}

pair<int, int> dfs(int y, int x)
{
    visited[y][x] = true;
    pair<int, int> res = {0, 0};
    if (map[y][x] == 'o') // 양
        res.first++;
    if (map[y][x] == 'v') // 늑대
        res.second++;
    for (int d = 0; d < 4; d++)
    {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || ny >= R || nx < 0 || nx >= C)
            continue;
        if (visited[ny][nx] || map[ny][nx] == '#')
            continue;
        pair<int, int> tmp = dfs(ny, nx);
        res.first += tmp.first;
        res.second += tmp.second;
    }
    return res;
}

void solution()
{
    int sheep = 0, wolf = 0;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (visited[i][j] || map[i][j] == '#')
                continue;
            pair<int, int> res = dfs(i, j);
            if (res.first > res.second)
                sheep += res.first;
            else
                wolf += res.second;
        }
    }
    cout << sheep << " " << wolf;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}