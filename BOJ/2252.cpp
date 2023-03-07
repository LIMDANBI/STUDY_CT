#include<iostream>
#include<vector>
#include<queue>
#define MAX 32001
using namespace std;

int N, M;
int indegree[MAX]; // 진입차수
vector<int> v[MAX];

void input() {
	cin >> N >> M;

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		indegree[b]++;
	}
}

void solution() {
	vector<int> ans;
	queue<int> q;

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		ans.push_back(cur);

		for (int next = 0; next < v[cur].size(); next++) {
			if (--indegree[v[cur][next]] == 0) q.push(v[cur][next]);
		}
	}

	for (int i = 0; i < N; i++) cout << ans[i] << " ";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}