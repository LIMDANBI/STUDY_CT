#include <iostream>
#include <vector>
#define MAX 1000001
using namespace std;

struct INFO
{
    int prev;
    int next;
};

int N, M;
vector<INFO> station(MAX);

void input()
{
    cin >> N >> M;

    int prev, start, end;
    cin >> start;
    prev = start;

    int num;
    for (int i = 1; i < N - 1; i++)
    {
        cin >> num;
        station[prev].next = num;
        station[num].prev = prev;
        prev = num;
    }

    cin >> end;
    station[prev].next = end;
    station[end].prev = prev;
    station[end].next = start;
    station[start].prev = end;
}

void BN(int i, int j)
{
    cout << station[i].next << "\n"; // 고유 번호 i를 가진 역의 다음 역의 고유 번호
    if (station[j].prev != 0)        // 이미 설립된 역
        return;

    // 그 사이에 고유 번호 j인 역을 설립
    station[j].prev = i;
    station[j].next = station[i].next;
    station[station[i].next].prev = j;
    station[i].next = j;
}

void BP(int i, int j)
{
    cout << station[i].prev << "\n"; // 고유 번호 i를 가진 역의 이전 역의 고유 번호
    if (station[j].prev != 0)        // 이미 설립된 역
        return;

    // 그 사이에 고유 번호 j인 역을 설립
    station[j].prev = station[i].prev;
    station[j].next = i;
    station[station[i].prev].next = j;
    station[i].prev = j;
}

void CN(int i)
{
    int deleted = station[i].next;
    cout << deleted << "\n"; // 고유 번호 i를 가진 역의 다음 역의 고유 번호

    // 고유 번호 i를 가진 역의 다음 역 폐쇄
    station[i].next = station[station[i].next].next;
    station[station[i].next].prev = i;
    station[deleted] = {0, 0};
}

void CP(int i)
{
    int deleted = station[i].prev;
    cout << deleted << "\n"; //  고유 번호 i를 가진 역의 이전 역의 고유 번호

    // 고유 번호 i를 가진 역의 이전 역 폐쇄
    station[i].prev = station[station[i].prev].prev;
    station[station[i].prev].next = i;
    station[deleted] = {0, 0};
}

void solution()
{
    int i, j;
    string cmd;
    while (M--)
    {
        cin >> cmd;
        if (cmd == "BN")
        {
            cin >> i >> j;
            BN(i, j);
        }
        else if (cmd == "BP")
        {
            cin >> i >> j;
            BP(i, j);
        }
        else if (cmd == "CN")
        {
            cin >> i;
            CN(i);
        }
        else if (cmd == "CP")
        {
            cin >> i;
            CP(i);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}