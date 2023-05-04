#include <iostream>
#include <cstring>
#define MAX 21
using namespace std;

int N, ans;
int map[MAX][MAX];
bool isCheck[101];
int dy[] = {1, 1, -1, -1};
int dx[] = {1, -1, -1, 1};

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    }
}

int get_desert_num(int y, int x, int w, int h)
{

    int cnt = 0;
    int ny = y, nx = x, tmp;
    for (int d = 0; d < 4; d++)
    {
        d == 0 || d == 2 ? tmp = w : tmp = h;
        for (int i = 0; i < tmp; i++)
        {
            ny += dy[d];
            nx += dx[d];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || isCheck[map[ny][nx]])
                return -1;
            isCheck[map[ny][nx]] = true;
            cnt++;
        }
    }
    return cnt;
}

void solution()
{
    ans = -1; // init

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {

            for (int w = 1; w < N; w++)
            {
                for (int h = 1; h < N; h++)
                {
                    memset(isCheck, false, sizeof(isCheck)); // init
                    ans = max(ans, get_desert_num(y, x, w, h));
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("../input.txt", "r", stdin);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        input();
        solution();
        cout << "#" << t << " " << ans << "\n";
    }
}