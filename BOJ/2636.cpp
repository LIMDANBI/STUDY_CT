#include <iostream>
#include <queue>
#define MAX 101
#define EMPTY 0
#define CHEESE 1
using namespace std;

struct POS
{
    int r, c;
};

int R, C;
int total = 0;
int map[MAX][MAX];
bool visited[MAX][MAX];
bool tmp_visisted[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void input()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> map[i][j];
            total += map[i][j]; // 치즈 조각이 놓여 있는 칸 수
        }
    }
}

void check_not_cheese(queue<POS> &q)
{
    while (!q.empty())
    {
        int r = q.front().r;
        int c = q.front().c;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;
            if (map[nr][nc] == CHEESE || visited[nr][nc])
                continue;
            visited[nr][nc] = true;
            q.push({nr, nc});
        }
    }
}

void melted_cheese(queue<POS> &q)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            tmp_visisted[i][j] = visited[i][j];
    }

    for (int r = 1; r < R - 1; r++)
    {
        for (int c = 1; c < C - 1; c++)
        {
            if (map[r][c] == EMPTY)
                continue;
            for (int d = 0; d < 4; d++)
            {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (tmp_visisted[nr][nc])
                {
                    visited[nr][nc] = true;
                    map[r][c] = EMPTY;
                    q.push({nr, nc});
                    break;
                }
            }
        }
    }
}

void solution()
{
    int sy[] = {0, 0, R - 1, R - 1};
    int sx[] = {0, C - 1, 0, C - 1};

    queue<POS> q;
    for (int i = 0; i < 4; i++)
    {
        q.push({sy[i], sx[i]});
        visited[sy[i]][sx[i]] = true;
    }

    for (int t = 1;; t++)
    {
        check_not_cheese(q);
        melted_cheese(q);
        if (q.size() == total)
        {
            cout << t << "\n"
                 << total;
            return;
        }
        else
            total -= q.size();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    if (total)
        solution();
    else
        cout << 0 << "\n"
             << 0;
}