#include<iostream>
#define MAX 10001
using namespace std;

int N;
double num[MAX];

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> num[i];
}

void solve() {
	double ans = 0, mul = 0;
	for (int i = 0; i < N; i++) {
		if (mul < 1) mul = num[i];
		else  mul *= num[i];
		ans = max(ans, mul);
	}

	cout << fixed;
	cout.precision(3);
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}