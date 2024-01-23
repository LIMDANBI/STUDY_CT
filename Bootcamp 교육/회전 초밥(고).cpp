#include<iostream>
#include<vector>
#define MAX 3001
using namespace std;

int N, d, k, c;
int cnt[MAX];
vector<int> sushi;

void input() {
    cin >> N >> d >> k >> c;

    int n;
    for (int i = 0; i < N; i++) {
        cin >> n;
        sushi.push_back(n);
    }
}

void solve() { // 주어진 회전 초밥 벨트에서 먹을 수 있는 초밥의 가짓수의 최대값
    int ans = 0, sum = 1;
    cnt[c] = 1; // 쿠폰으로 먹을 수 있는 초밥

    // 1. 처음(0부터) k 개
    for (int i = 0; i < k; i++) {
        if (cnt[sushi[i]]++ == 0) sum++;
    }
    ans = sum;

    // 2. 슬라이딩 윈도우 + 투 포인터 (k...N 부터 k개)
    int l = 0, r = k;
    for (int i = 0; i < N; i++) {

        if (--cnt[sushi[l++]] == 0) sum--; // left
        if (cnt[sushi[r++]]++ == 0) sum++; // right

        // 값 갱신
        ans = max(ans, sum);
        if(r > N) r = 0;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}