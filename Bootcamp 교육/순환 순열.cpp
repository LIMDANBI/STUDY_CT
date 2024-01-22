#include<iostream>
#include<vector>
#define MAX 100
using namespace std;

int N, P;
int cnt[MAX];

void input() {
	cin >> N >> P;
}

int solve() { // 반복되는 부분에 포함된 서로 다른 숫자의 개수
	int before = N;
	for (int i = 0; ; i++) { 
		int val = (before * N) % P;
		if (cnt[val] != 0) return (i-cnt[val]); 
		cnt[val] = i; // 순서 저장
		before = val; // 값 갱신
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	cout << solve();
}