#include<iostream>
#include<queue>
#define MAX 1001
using namespace std;

struct DATA { 
	int a, b, c; 
	bool operator < (const DATA &d) const {
		return c > d.c;
	}
};

int N, M;
int root[MAX];
char gender[MAX];

int find_(int a) {
	if (a == root[a]) return a;
	return root[a] = find_(root[a]);
}

void union_(int a, int b) {
	root[find_(b)] = find_(a);
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> gender[i];
		root[i] = i;
	}

	priority_queue<DATA> pq;
	int a, b, c;
	while (M--) {
		cin >> a >> b >> c;
		pq.push({ a,b,c });
	}

	int ans = 0, edge = 0;
	while (!pq.empty()) {
		a = pq.top().a;
		b = pq.top().b;
		c = pq.top().c;
		pq.pop();

		if (find_(a) == find_(b)) continue;
		if (gender[a] == gender[b]) continue;
		union_(a, b);
		ans += c;
		if (++edge == N - 1) break;
	}

	edge == N - 1 ? cout << ans : cout <<-1;
}