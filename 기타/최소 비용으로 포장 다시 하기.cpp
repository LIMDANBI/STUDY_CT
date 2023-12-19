#include <iostream>
#include <queue>
using namespace std;

int N, ni;
priority_queue<int, vector<int>, greater<int>> pq; // 22ms

void input(){
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> ni;
        pq.push(ni);
    }
}

void solve(){
    int ans = 0;
    while (!pq.empty()){
        int a = pq.top(); pq.pop();
        if(pq.empty()) break;
        else{
            int b = pq.top(); pq.pop();
            pq.push(a+b);
            ans+=(a+b);
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}

// qsort (stdlib.h) // 390ms
// sort(candy+i, candy+N); // 179ms 
// simple sort : 52ms