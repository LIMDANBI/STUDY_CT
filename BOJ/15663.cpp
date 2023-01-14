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

void solution(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) cout << ans[i] << " ";
		cout << "\n";
		return;
	}

    int prev = -1; // 중복 수열 방지
	for (int i = 0; i < N; i++) {
        if(isused[i] || num[i] == prev) continue;
        isused[i] = true;
		ans[cnt] = num[i];
        prev = num[i];
		solution(cnt + 1);
        isused[i] = false;
	}
}

int main() {
	input();
	solution(0);
}