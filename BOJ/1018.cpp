#include <iostream>
#define MAX 51
using namespace std;

int N, M;
string board[MAX];

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> board[i];
}

int get_recoloring_cnt(int r, int c)
{
    int first_black = 0; // 첫 칸을 블랙으로 칠하는 경우
    int first_white = 0; // 첫 칸을 화이트로 칠하는 경우

    for (int i = r; i < r + 8; i++)
    {
        for (int j = c; j < c + 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                if (board[i][j] != 'B')
                    first_black++;
                else
                    first_white++;
            }
            else
            {
                if (board[i][j] != 'W')
                    first_black++;
                else
                    first_white++;
            }
        }
    }
    return min(first_black, first_white);
}

void solution()
{
    int ans = MAX * MAX;
    for (int i = 0; i <= N - 8; i++)
    {
        for (int j = 0; j <= M - 8; j++)
            ans = min(ans, get_recoloring_cnt(i, j));
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}