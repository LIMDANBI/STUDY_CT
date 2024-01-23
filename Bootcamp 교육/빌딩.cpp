#include<iostream>
using namespace std;

int N;

void input() {
	cin >> N;
}

bool includeFour(int n) {
	while (n) {
		if (n % 10 == 4) return true;
		n /= 10;
	}
	return false;
}

void solve() { // 실제 층 수를 출력
	int ans = N;
	for (int n = 1; n <= N; n++) {
		if (includeFour(n)) ans--;
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}