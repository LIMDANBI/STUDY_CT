#include<iostream>
#include<algorithm>
#include<vector>
#define pii pair<int, int>
using namespace std;

int N, S, E;
int longtime, shorttime;
vector<pii> v;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S >> E;
        v.push_back({ S, E });
    }
}

void solve() {

    // 1. 입장 시간을 기준으로 정렬
    sort(v.begin(), v.end());
    int prv = v[0].second;
    int tmp = v[0].second - v[0].first;

    // 2. 한 명 이상이 머물렀던 가장 긴 시간, 한 명도 머물지 않았던 가장 긴 시간 구하기
    for (int i = 1; i < N; i++) {
        if (v[i].first > prv) { // 머무는 학생이 없는 경우
            shorttime = max(shorttime, v[i].first - prv);
            tmp = v[i].second - v[i].first;
        }
        else if (v[i].second > prv) { // 머무는 학생이 한명 이상 있는 경우
            tmp += (v[i].second - prv);
        }
        prv = max(prv, v[i].second);
        longtime = max(longtime, tmp);
    }

    // 3. 정답 출력
     cout << longtime << " " << shorttime;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}