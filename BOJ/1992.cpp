#include<iostream>
#include<string>
#define MAX 64
using namespace std;

int N;
string map[MAX];

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> map[i];
}

void solution(int y, int x, int l) { // 왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래,
	int sum =  0;
	for (int i = y; i < y + l; i++) {
		for (int j = x; j < x + l; j++) sum += map[i][j] - '0';
	}

	if (sum == l * l) cout << 1;
	else if (sum == 0) cout << 0;
	else {
		cout << "(";
		int half = l / 2;
		solution(y, x, half);
		solution(y, x+half, half);
		solution(y+half, x, half);
		solution(y+half, x+half, half);
		cout << ")";
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	// freopen("input.txt", "r", stdin); // task /f /PID [pid]
	input();
	solution(0, 0, N);
}