#include <iostream>
#include <queue>
#define EMPTY 0
using namespace std;

int N, M;
int cost[101], parkinglot[101], weight[2001];

void input() {
  cin >> N >> M;               // 주차공간, 차량
  for (int i = 1; i <= N; i++) // 단위 무게 당 요금
    cin >> cost[i];
  for (int i = 1; i <= M; i++) // 차량들의 무게를 나타내는 정수
    cin >> weight[i];
}

void solution() {
  queue<int> q;
  int car, ans = 0, cnt = 0, inout = 2 * M;
  while (inout--) {
    cin >> car;
    if (car > 0) // in
    {
      if (cnt < N) // 주차장에 자리가 있는 경우
      {
        cnt++;
        for (int i = 1; i <= N; i++) {
          if (parkinglot[i] == EMPTY) {
            parkinglot[i] = car;
            ans += cost[i] * weight[car];
            break;
          }
        }
      } else // 대기해야하는 경우
        q.push(car);
    } else // out
    {
      cnt--;
      for (int i = 1; i <= N; i++) {
        if (parkinglot[i] == car * -1) // 주차되어 있던 차가 나가는 경우
        {
          parkinglot[i] = EMPTY;
          if (!q.empty()) // 대기차가 있는 경우
          {
            parkinglot[i] = q.front();
            ans += cost[i] * weight[q.front()];
            q.pop();
            cnt++;
          }
          break;
        }
      }
    }
  }
  cout << ans;
}

int main() {
  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  input();
  solution();
}