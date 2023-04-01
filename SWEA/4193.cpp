#include <iostream>
#include <cstring>
#include <queue>
#define MAX 16
#define EMPTY 0
#define WALL 1 // 섬과 같은 장애물
#define EDDY 2 // 생성되고 2초동안 유지되다가 1초동안 잠잠
using namespace std;

struct DATA
{
    int y, x, s; // 좌표(y, x) 현재초(s)
};

int N;
int sy, sx; // 시작점
int ey, ex; // 도착점
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    }
    cin >> sy >> sx;
    cin >> ey >> ex;
}

int solution()
{
    queue<DATA> q;
    q.push({sy, sx, 0});
    visited[sy][sx] = true;

    while (!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        int s = q.front().s;
        q.pop();

        if (y == ey && x == ex)
            return s;

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N)
                continue;
            if (map[ny][nx] == WALL || visited[ny][nx]) // 장애물인 경우, 이미 방문한 경우
                continue;
            if ((map[ny][nx] == EDDY && s % 3 == 2) || map[ny][nx] == EMPTY)
            { // 지나갈 수 있는 경우
                visited[ny][nx] = true;
                q.push({ny, nx, s + 1});
            }
            else // 소용돌이가 잠잠해지기를 대기
                q.push({y, x, s + 1});
        }
    }
    return -1; // 도착할 수 없는 경우
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        input();
        memset(visited, false, sizeof(visited)); // init
        cout << "#" << t << " " << solution() << "\n";
    }
}