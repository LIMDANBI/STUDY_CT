#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 2001
using namespace std;

struct PARCEL {
    int s, e, c;
    bool operator < (const PARCEL &p) const {
        if(e == p.e) return s < p.s;
        return e < p.e;
    }
};

int N, C, M;
int capacity[MAX];
vector<PARCEL> parcel;

void input() {
    cin >> N >> C >> M;

    int s, e, c;
    for (int i = 0; i < M; i++) {
        cin >> s >> e >> c;
        parcel.push_back({ s, e, c });
    }
}

void solve() { // 트럭 한 대로 배송할 수 있는 최대 박스 수 구하기

    // 1. 도착지를 기준으로 오름차순 정렬    
    sort(parcel.begin(), parcel.end());

    // 2. 각 지점에서 실을 수 있는 양 구하기
    int ans=0;
    for(auto p : parcel){
        int max_cap=0, send=0;
        for(int i=p.s; i<p.e; i++) max_cap = max(max_cap, capacity[i]);
        send = min(C-max_cap, p.c);
        ans += send;
        for(int i=p.s; i<p.e; i++) capacity[i]+=send;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}