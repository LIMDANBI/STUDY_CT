#include<iostream>
#define MAX 10
using namespace std;

int N, M;
int num[MAX], isused[MAX];

void solution(int cnt) {
	if (cnt > M) {
		for (int i = 1; i <= M; i++) cout << num[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (isused[i]) continue;
		isused[i] = true;
		num[cnt] = i;
		solution(cnt + 1);
		isused[i] = false;
	}
}

int main() {
	cin >> N >> M;
	solution(1);
}