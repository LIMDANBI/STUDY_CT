#include <iostream>
#include <vector>
using namespace std;

struct ROOM
{
    int t, a, h;
};
vector<ROOM> rooms;

int N, HATK;

void input()
{
    cin >> N >> HATK; // 방의 개수, 초기 공격력

    int t, a, h;
    for (int i = 0; i < N; i++)
    {
        // ti = 1, 공격력이 ai이고 생명력이 hi인 몬스터
        // ti = 2, HATK를 ai만큼 증가, HCurHP를 hi만큼 회복
        cin >> t >> a >> h;
        rooms.push_back({t, a, h});
    }
}

bool ispossble(long long HMaxHP)
{
    long long atk = HATK, curHP = HMaxHP;

    int t, a, h;
    for (int i = 0; i < N; i++)
    {
        t = rooms[i].t; // 몬스터, 회복
        a = rooms[i].a; // 공격력, HATK
        h = rooms[i].h; // 생명력, HCurHP

        if (t == 1)
        {
            long long cnt = h / atk; // 공격횟수
            if (h % atk == 0)        // 몬스터가 죽은 이후 용사는 공격을 받지 않음
                cnt--;
            curHP -= cnt * a;
            if (curHP <= 0)
                return false;
        }
        else
        {
            atk += a;
            curHP = min(HMaxHP, curHP + h);
        }
    }
    return true;
}

void solution() // 용사가 N번째 방에 있는 용을 쓰러트리기 위한 최소의 HMaxHP
{
    long long low = 0, mid, high = N * 1e6 * 1e6;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ispossble(mid))
            high = mid - 1;
        else
            low = mid + 1;
    }
    cout << low;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}