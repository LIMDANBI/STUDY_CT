#include<iostream>
#include<algorithm>
#define INF 1000000001
#define MAX_HOME 200001
using namespace std;

int N, C;
int home[MAX_HOME];

void input() {
	cin >> N >> C;
	for (int i = 0; i < N; i++) cin >> home[i];
	sort(home + 0, home + N); // 정렬
}

bool check(int len) {
	int before=home[0], cnt=1; // 기준, 공유기 개수
	for (int i = 1; i < N; i++) {
		if (len <= home[i] - before) {
			before = home[i];
			cnt++;
		}
	}
	if (cnt < C) return false;
	return true;
}

void solution() { // 가장 인접한 두 공유기 사이의 최대 거리
	int low = 0, high = INF;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (check(mid)) low = mid + 1; // 더 넓게 공유기를 설치할 수 있는 경우
		else high = mid - 1; // 공유기를 더 좁게 설치해야 하는 경우
	} cout << high;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}