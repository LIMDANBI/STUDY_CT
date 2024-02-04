#include<iostream>
#include<queue>
using namespace std;

int N; // 직원수
int S; // 시작 번호
int M;

void input(){
    cin >> N >> S >> M;
}

void solve(){

    queue<int> q;
    
    // 1. 직원을 큐에 넣기
    for (int i = 0; i < N; i++){
        if(S+i <= N) q.push(S+i);
        else q.push(S+i-N);
    }

    // 2. 장기자랑 순서 출력
    int cnt = 1;
    while(!q.empty()){
        if(cnt%M == 0) cout << q.front() << " ";
        else  q.push(q.front());
        q.pop();
        cnt++;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}