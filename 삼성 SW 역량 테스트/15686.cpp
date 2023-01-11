#include<iostream>
#include<vector>
#define MAX 14
#define INF 1000000001
#define EMPTY 0
#define HOUSE 1
#define CHICKEN 2
using namespace std;

int selected[MAX];
int N, M, ans = INF;
vector<pair<int, int>> house, chicken;

void input() {
	cin >> N >> M;

	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			if (tmp == HOUSE) house.push_back({ i, j }); // 집
			if (tmp == CHICKEN) chicken.push_back({ i, j }); // 치킨 집
		}
	}
}

void solution(int idx, int cnt) {
	if (cnt == M) { // M개의 치킨집 모두 선택
		int dist = 0;
		for (int i = 0; i < house.size(); i++) { // (집, 치킨집) 맨해튼 거리
			int res = INF;
			for (int j = 0; j < M; j++) {
				int ny = abs(house[i].first - chicken[selected[j]].first);
				int nx = abs(house[i].second - chicken[selected[j]].second);
				res = min(res, ny+nx);
			}
			dist += res;
		}
		ans = min(ans, dist);
		return;
	}

	for (int i = idx; i < chicken.size(); i++){
		selected[cnt] = i;
		solution(i + 1, cnt + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0, 0);
	cout << ans;
}