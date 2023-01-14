#include<iostream>
#define MAX 10
using namespace std;

int N, M;
int num[MAX];

void solution(int idx, int cnt) {
	if (cnt > M) {
		for (int i = 1; i <= M; i++) cout << num[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = idx; i <= N; i++) {
		if (num[cnt - 1] > i) continue;
		num[cnt] = i;
		solution(i + 1, cnt + 1);
	}
}

int main() {
	cin >> N >> M;
	solution(1, 1);
}