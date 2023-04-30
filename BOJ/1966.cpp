#include <iostream>
#include <queue>
using namespace std;

int solution() {
  int N, M;
  cin >> N >> M;

  queue<pair<int, int>> q; // 번호, 중요도
  for (int i = 0; i < N; i++) {
    int priority;
    cin >> priority;
    q.push({i, priority});
  }

  int ans = 0;
  while (true) {
    bool ispop = true;
    int qsize = q.size();
    int front_priority = q.front().second; // 가장 앞에 있는 문서의 ‘중요도’

    // 나머지 문서의 중요도 확인
    while (qsize--) {
      q.push(q.front());
      q.pop();
      if (front_priority < q.front().second)
        ispop = false;
    }

    if (ispop) { // 중요도가 가장 높은 경우, 바로 인쇄
      ans++;
      if (q.front().first == M)
        return ans;
      q.pop();
    } else { // 중요도가 높은 문서가 하나라도 있는 경우, 가장 뒤에 재배치
      q.push(q.front());
      q.pop();
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    cout << solution() << "\n";
}