#include<iostream>
#define MAX 10
using namespace std;

int N;
int nums[MAX];

void input() {
	cin >> N;
}

int change(int n) { // 4보다 큰 수 - 1
	int res = 0, idx = 0, r;
	while (n) {
		r = n % 10;
		n /= 10;
		if (r >= 4) nums[idx++] = r-1;
		else nums[idx++] = r;
	}
	return idx;
}

int changeDigit(int idx) { // 9 -> 10 진법
	int ans = 0, n = 1;
	for (int i = 0; i <= idx; i++) {
		ans += (nums[i] * n);
		n *= 9;
	}
	return ans;
}

void solve() { // 실제 층 수를 출력
	int idx = change(N);
	cout << changeDigit(idx);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}