#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;
vector<pair<int, int>> v;

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        int x, y; cin >> x >> y;
        v.push_back({y, x});
    }
}

void solve(){

    // 1. 최고 보관 온도를 기준으로 정렬
    sort(v.begin(), v.end());

    // 2. 필요한 최소 냉장고 대수 구하기
    int ans=0, temp=-300;
    for(auto c : v){
        if(c.second > temp){
            temp = c.first;
            ans++;
        }
    }
    cout << ans;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}