#include<iostream>
#include<cstring>
#define MAX 1001
using namespace std;

int N;
bool used[MAX];

void input() {
	cin >> N;
}

int sqsum(int n) {
	int sum = 0;
	while (n) {
		sum += (n % 10) * (n % 10);
		n /= 10;
	}
	return sum;
}

bool isHappy(int n) {
	
	// 1. 초기화
	memset(used, false, sizeof(used));

	// 2. 행복한 수 인지 확인
	while (!used[n]) {
		used[n] = true;
		n = sqsum(n);
		if (n == 1) return true;
	}
	return false;
}

int solve() {
	for (int n = N; n > 0; n--) { // 가장 큰 행복한 수
		if (isHappy(n)) return n;
	}
	return -1; // 디버깅을 위해
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	cout << solve();
}