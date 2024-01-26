#include<iostream>
#include<stack>
using namespace std;

int N, H;

void input(){
    cin >> N;
}

void solve(){
    long long ans = 0;
    stack<int> s; // 나를 볼 수 있는 건물
    for(int i=0; i<N; i++){
        cin >> H;
        while(!s.empty() && s.top() <= H) s.pop();
        ans += s.size();
        s.push(H);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}