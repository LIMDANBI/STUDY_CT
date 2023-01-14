#include<iostream>
#include<algorithm>
#define MAX 10
using namespace std;

int N, M;
bool isused[MAX];
int num[MAX], ans[MAX];

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> num[i];
	sort(num, num + N);
}

void solution(int idx, int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) cout << ans[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = idx; i < N; i++) {
		ans[cnt] = num[i];
		solution(i, cnt + 1);
	}
}

int main() {
	input();
	solution(0, 0);
}