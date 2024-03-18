#include<iostream>
#include<queue>
using namespace std;

int N;
priority_queue<int> pq;

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int size;
        cin >> size;
        pq.push(-size);
    }
}

void solve(){ // 최소 비교 횟수 (그리디)
    int ans = 0;
    while (pq.size() > 1){
        int a = -pq.top(); pq.pop();
        int b = -pq.top(); pq.pop();
        pq.push(-(a + b));
        ans += (a + b);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("../test/input.txt", "r", stdin);
    input();
    solve();
}