#include<iostream>
#include<vector>
#define MAX 100
using namespace std;

int N, P;
int cnt[MAX];

void input() {
	cin >> N >> P;
}

void solve() { // 반복되는 부분에 포함된 서로 다른 숫자의 개수
	int before = N, ans = 0;
	for (int i = 0; ; i++) { 
		int val = (before * N) % P;
		cnt[val]++;
		before = val; // 값 갱신
		if (cnt[val] == 2) ans++;
		if (cnt[val] == 3) break;
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}