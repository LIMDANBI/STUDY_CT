#include <iostream>
using namespace std;

int dy[] = {0, -1, 0, 1}; // 우 상 좌 하
int dx[] = {1, 0, -1, 0};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int M, n;
    cin >> M >> n;

    string type;
    int cnt;

    int y = 0, x = 0, d = 0;
    while (n--)
    {
        cin >> type >> cnt;
        if (type == "TURN")
        {
            if (cnt == 0)
            { // 현재 위치에서 왼쪽으로 90도 회전
                if (--d < 0)
                    d = 3;
            }
            else
            { // 현재 위치에서 오른쪽으로 90도 회전
                if (++d >= 4)
                    d = 0;
            }
        }
        else
        {
            y += dy[d] * cnt;
            x += dx[d] * cnt;
            if (y < 0 || y >= M || x < 0 || x >= M)
            {
                cout << -1;
                return 0;
            }
        }
    }
    cout << x << " " << y;
}