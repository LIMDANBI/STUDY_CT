#include <iostream>
#include <string>
#define MAX 100001
using namespace std;

int N, M;
int power[MAX];
string name[MAX];

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> name[i];
        cin >> power[i];
    }
}

void solution()
{
    int p, low, mid, high;
    while (M--)
    {
        cin >> p;
        low = 0;
        high = N;

        while (low <= high)
        {
            mid = (low + high) / 2;
            if (p <= power[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        cout << name[low] << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}