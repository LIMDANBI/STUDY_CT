#include <iostream>
#define INF 1e9
using namespace std;

int N;//협찬 물품의 수
int D[100000 + 10];//선호도
int sol = -INF;// 최대 선호도

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> D[i];
	}
}

void solve(){
	int i, sum = 0;
	for (i = 0; i < N; i++) {
		if (sum > 0) sum += D[i];
		else sum = D[i];
		sol = max(sol, sum);
	}
	cout << sol << "\n";
}

int main() {
	input();
	solve();
}