#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;
vector<pair<int, int>> movie;

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        int s, e;
        cin >> s >> e;
        if(e-s < 2) continue; // 2시간 미만 영화
        movie.push_back({e, s});
    }
}

void solve(){
    int prv=0, cnt=0;

    // 1. 종료 시간을 기준으로 정렬
    sort(movie.begin(), movie.end());

    // 2. 시청할 수 있는 영화 카운팅
    for(auto m : movie){
        if(prv <= m.second){
            cnt++;
            prv = m.first;
        }
    }
    cout << cnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}