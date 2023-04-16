#include <iostream>
#define MAX 21
#define INF 1000001
using namespace std;

int N, B;
int ans;
int height[MAX];

void input() {
	ans = INF;
	cin >> N >> B;
	for (int i = 0; i < N; i++) cin >> height[i];
}

void solution(int cnt, int sum) {
	if (B <= sum) {
		int diff = sum - B;
		if (diff < ans) ans = diff;
		else return;
	}
	if (cnt == N) {
		return;
	}
	solution(cnt + 1, sum);
	solution(cnt + 1, sum + height[cnt]);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		input();
		solution(0, 0);
		cout << "#" << t << " " << ans << "\n";
	}
	return 0;
}