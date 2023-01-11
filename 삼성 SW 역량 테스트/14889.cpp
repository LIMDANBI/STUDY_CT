#include<iostream>
#include<vector>
#define MAX 21
#define INF 1000000001
using namespace std;

int N, ans = INF;
int score[MAX][MAX];
bool start_team[MAX];

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> score[i][j];
	}
}

void solution(int idx, int cnt) {
	if (cnt == N / 2) {
		int start = 0, link = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (start_team[i] == start_team[j]) {
					if (start_team[i]) start += (score[i][j] + score[j][i]);
					else link += (score[i][j] + score[j][i]);
				}
			}
		}
		ans = min(ans, abs(start - link));
		return;
	}
	for (int i = idx; i < N; i++) {
		start_team[i] = true;
		solution(i + 1, cnt + 1);
		start_team[i] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0, 0);
	cout << ans;
}