#include <iostream>
#include <queue>
#define MAX 501
#define DANGER 1
#define DEATH 2
using namespace std;

struct DATA
{
    int y, x, lose;
};

int N, M;
int map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void swap(int &a, int &b)
{
    if (b < a)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }
}

void check_zone(int y1, int x1, int y2, int x2, int zone)
{
    swap(y1, y2); // y1이 y2 보다 작음을 보장
    swap(x1, x2); // x1이 x2 보다 작음을 보장

    for (int y = y1; y <= y2; y++)
    {
        for (int x = x1; x <= x2; x++)
            map[y][x] = zone;
    }
}

void input()
{
    int y1, x1, y2, x2;

    cin >> N;
    while (N--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        check_zone(y1, x1, y2, x2, DANGER); // 위험 구역
    }

    cin >> M;
    while (M--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        check_zone(y1, x1, y2, x2, DEATH); // 죽음 구역
    }
}

int solution()
{
    deque<DATA> dq;
    visited[0][0] = true;
    dq.push_back({0, 0, 0});

    while (!dq.empty())
    {
        int y = dq.front().y;
        int x = dq.front().x;
        int lose = dq.front().lose;
        dq.pop_front();

        if (y == MAX - 1 && x == MAX - 1)
            return lose;

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) // 범위를 벗어나는 경우
                continue;
            if (visited[ny][nx] || map[ny][nx] == DEATH) // 이미 방문한 경우, 죽음의 구역인 경우
                continue;
            visited[ny][nx] = true;
            if (map[ny][nx] == DANGER)            // 위험한 구역인 경우
                dq.push_back({ny, nx, lose + 1}); // 뒤에 넣어줌!!
            else
                dq.push_front({ny, nx, lose}); // 앞에 넣어줌!!
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    cout << solution(); // 잃는 생명의 최솟값
}