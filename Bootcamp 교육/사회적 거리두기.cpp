#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 100005
using namespace std;

struct INTERVAL{
    long long s, e;
    bool operator < (INTERVAL const &itv) const{
        if(s == itv.s) return e < itv.e;
        return s < itv.s;
    }
};

int N, M; // 소마리수, 잔디구간 개수
vector<INTERVAL> v; // 잔디 구간 시작, 끝

void input(){
    cin >> N >> M;
    v.resize(M); // 크기 조정
    for(int i=0; i<M; i++) cin >> v[i].s >> v[i].e;
}

bool check(long long D){
    long long cnt = 0; // 소가 있을 수 있는 위치 개수
    long long idx = -D; // 마지막 소의 위치
    long long s, e, d, q, r;
    for(auto itv : v){
        s = max(itv.s, idx+D);
        e = itv.e;
        if(e < s) continue;
        d = e - s;
        q = d / D;
        r = d % D;
        cnt += (q+1);
        idx = e - r;
    }
    return N <= cnt;
}

void solve(){

    // 1. 구간 오름차순 정렬
    sort(v.begin(), v.end());

    // 2. 이분탐색
    long long low=0, mid, high=1e18;
    while (low <= high){
        mid = (low+high)/2;
        if(check(mid)) low = mid+1;
        else high = mid-1;
    }
    cout << high; // 가능한 최대값 D  
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}