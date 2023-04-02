// 주의할 점
// 1. 진사람이 먼저 총을 버려야 한다. (해당 총이 제일 클 수도 있으므로)
// 2. 총을 내려놓고 0으로 설정해줘야 한다!! push만 해주고 설정을 안해줬었다,,

#include <iostream>
#include <vector>
#define MAX 21
#define MAXP 31
using namespace std;

struct PLAYER
{
    int y, x, d, s, g; // 좌표, 방향, 초기능력치, 총
};
vector<PLAYER> players(MAXP);

int N, M, K;
int score[MAXP];
int pNum[MAX][MAX];
vector<int> map[MAX][MAX];
int dy[] = {-1, 0, 1, 0}; // 상 우 하 좌
int dx[] = {0, 1, 0, -1};

void input()
{
    cin >> N >> M >> K;

    // map (N*N)
    int gun;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> gun;
            if (gun != 0)
                map[i][j].push_back(gun);
        }
    }

    // plaeyr
    int y, x, d, s;
    for (int num = 1; num <= M; num++)
    {
        cin >> y >> x >> d >> s;
        pNum[y - 1][x - 1] = num; // player 번호
        players[num] = {y - 1, x - 1, d, s, 0};
    }
}

int get_gun(int y, int x, int g)
{
    int max_gun = g, max_idx = -1;
    for (int i = 0; i < map[y][x].size(); i++)
    {
        if (max_gun < map[y][x][i])
        {
            max_idx = i;
            max_gun = map[y][x][i];
        }
    }
    if (max_idx != -1)
    {
        map[y][x][max_idx] = g;
        return max_gun; // 공격력이 더 쎈 총을 획득
    }
    return g;
}

void solution()
{
    int y, x, d, s, g, ny, nx;
    int oNum, oy, ox, od, os, og;
    for (int num = 1; num <= M; num++) // player 번호 순서대로 이동
    {
        y = players[num].y;
        x = players[num].x;
        d = players[num].d;
        s = players[num].s;
        g = players[num].g;
        pNum[y][x] = 0;

        ny = y + dy[d];
        nx = x + dx[d];
        if (ny < 0 || ny >= N || nx < 0 || nx >= N) // 범위를 벗어나는 경우
        {
            d = (d + 2) % 4;
            ny = y + dy[d];
            nx = x + dx[d];
        }

        if (pNum[ny][nx] == 0)      // 다른 player가 없는 경우
            g = get_gun(ny, nx, g); // 가장 공격력이 높은 총을 획득
        else                        // 다른 player가 있는 경우
        {
            oNum = pNum[ny][nx];
            oy = ny;
            ox = nx;
            od = players[oNum].d;
            os = players[oNum].s;
            og = players[oNum].g;
            pNum[oy][ox] = 0;

            if ((os + og < s + g) || ((os + og == s + g) && os < s)) // 내가 이기는 경우
            {
                score[num] += (s + g - (os + og));

                // LOSE PLAEYR (other)
                // 본인이 가지고 있는 총을 해당 격자에 내려놓고,
                if (og != 0)
                {
                    map[ny][nx].push_back(og);
                    og = 0; // 내려놓고 0으로 바꿔주기!!!!!!
                }

                // WIN PLAYER (me)
                // 승리한 칸에 떨어져 있는 총들과
                // 원래 들고 있던 총 중 가장 공격력이 높은 총을 획득
                g = get_gun(ny, nx, g);

                // "상대"가 원래 가지고 있던 방향대로 한 칸 이동
                // (빈칸을 찾기 위해 오른쪽으로 90도씩 회전)
                for (int dir = od; dir < od + 4; dir++)
                {
                    int nd = dir % 4;
                    int my = oy + dy[nd];
                    int mx = ox + dx[nd];
                    if (my < 0 || my >= N || mx < 0 || mx >= N || pNum[my][mx] != 0)
                        continue; // 다른 플레이어가 있거나 격자 범위 밖인 경우
                    od = dir % 4;
                    break;
                }
                oy += dy[od];
                ox += dx[od];

                // 만약 해당 칸에 총이 있다면,
                // 가장 공격력이 높은 총을 획득
                og = get_gun(oy, ox, og);
            }
            else // 상대가 이기는 경우
            {
                score[oNum] += (os + og - (s + g));

                // LOSE PLAEYR (me)
                // 본인이 가지고 있는 총을 해당 격자에 내려놓고,
                if (g != 0)
                {
                    map[ny][nx].push_back(g);
                    g = 0; // 내려놓고 0으로 바꿔주기!!!!!!
                }

                // WIN PLAYER (other)
                // 승리한 칸에 떨어져 있는 총들과
                // 원래 들고 있던 총 중 가장 공격력이 높은 총을 획득
                og = get_gun(oy, ox, og);

                // "내"가 원래 가지고 있던 방향대로 한 칸 이동
                // (빈칸을 찾기 위해 오른쪽으로 90도씩 회전)
                for (int dir = d; dir < d + 4; dir++)
                {
                    int nd = dir % 4;
                    int my = ny + dy[nd];
                    int mx = nx + dx[nd];
                    if (my < 0 || my >= N || mx < 0 || mx >= N || pNum[my][mx] != 0)
                        continue; // 다른 플레이어가 있거나 격자 범위 밖인 경우
                    d = dir % 4;
                    break;
                }
                ny += dy[d];
                nx += dx[d];

                // 만약 해당 칸에 총이 있다면,
                // 가장 공격력이 높은 총을 획득
                g = get_gun(ny, nx, g);
            }

            // 상대 정보 update
            pNum[oy][ox] = oNum;
            players[oNum] = {oy, ox, od, os, og};
        }

        // 내 정보 update
        pNum[ny][nx] = num;
        players[num] = {ny, nx, d, s, g};
    }
}

void output()
{
    for (int i = 1; i <= M; i++)
        cout << score[i] << " ";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    while (K--)
        solution(); // k 라운드 동안 게임을 진행하면서
    output();       // 각 플레이어들이 획득한 포인트
}