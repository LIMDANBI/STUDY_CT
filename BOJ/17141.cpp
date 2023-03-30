#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define INF 10001
#define MAX 51
#define EMPTY 0
#define WALL 1
#define VIRUS 2
using namespace std;

struct POS
{
    int y, x;
};
vector<POS> candidate, virus;

int N, M;
int ans = INF; // 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간
int emptyCnt = 0;
int map[MAX][MAX], spreadTime[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == EMPTY)
                emptyCnt++;
            else if (map[i][j] == VIRUS)
            {
                candidate.push_back({i, j});
                map[i][j] = EMPTY;
                emptyCnt++;
            }
        }
    }
}

int spread_virus()
{
    queue<POS> q;
    int spread = M;
    if (spread == emptyCnt) // 빈칸이 없는 경우
        return 0;
    for (int i = 0; i < M; i++)
    {
        q.push(virus[i]);
        spreadTime[virus[i].y][virus[i].x] = 1;
    }

    while (!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N) // 범위를 벗어나는 경우
                continue;
            if (spreadTime[ny][nx] || map[ny][nx] != EMPTY) // 이미 방문한 경우, 빈칸이 아닌 경우
                continue;
            if (++spread == emptyCnt) // 모든 빈 칸에 바이러스를 퍼뜨린 경우
                return spreadTime[y][x];
            spreadTime[ny][nx] = spreadTime[y][x] + 1;
            q.push({ny, nx});
        }
    }
    return INF;
}

void solution(int start, int cnt)
{
    if (cnt == M)
    {
        memset(spreadTime, 0, sizeof(spreadTime));
        ans = min(ans, spread_virus()); // 시간 (모든 빈칸에 바이러스가 퍼진 경우) / INF
        return;
    }
    for (int i = start; i < (int)candidate.size(); i++)
    {
        virus.push_back(candidate[i]);
        solution(i + 1, cnt + 1);
        virus.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution(0, 0);
    ans == INF ? cout << -1 : cout << ans;
}