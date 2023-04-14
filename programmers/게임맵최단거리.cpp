#include <vector>
#include <queue>
#define MAX 101
using namespace std;

struct DATA
{
  int y, x, cnt;
};
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int solution(vector<vector<int>> maps)
{
  int N = (int)maps.size(), M = (int)maps[0].size();

  queue<DATA> q;
  q.push({0, 0, 1});
  visited[0][0] = true;

  while (!q.empty())
  {
    int y = q.front().y;
    int x = q.front().x;
    int cnt = q.front().cnt;
    q.pop();

    if (y == N - 1 && x == M - 1)
      return cnt;

    for (int d = 0; d < 4; d++)
    {
      int ny = y + dy[d];
      int nx = x + dx[d];
      if (ny < 0 || ny >= N || nx < 0 || nx >= M)
        continue;
      if (visited[ny][nx] || !maps[ny][nx])
        continue;
      visited[ny][nx] = true;
      q.push({ny, nx, cnt + 1});
    }
  }

  return -1;
}