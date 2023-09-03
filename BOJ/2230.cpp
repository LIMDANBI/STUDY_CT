#include<iostream>
#include<algorithm>
#define MAX 100001
using namespace std;

int N, M;
int num[MAX];

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> num[i];
}

void solution() {
	sort(num, num + N);

	int ans = 2000000001, l = 0, r = 1, diff;
	while (r < N) {
        diff = num[r] - num[l];
        if (diff >= M) {
			ans = min(ans, diff);
			l++;
		}
		else r++;
	}
    cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}