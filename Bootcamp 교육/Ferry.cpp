#include<iostream>
#include<queue>
#define MAX 10001
using namespace std;

int M, T, N;
queue<int> q[2];
int st[MAX], dt[MAX];

void input(){
    cin >> M >> T >> N;
    string d;
    for(int idx=0; idx<N; idx++){
        cin >> st[idx] >> d;
        if(d == "left") q[0].push(idx);
        else q[1].push(idx);
    }
}

void ride(int nd, int nt){
    int cnt = 0;
    while(cnt<M && !q[nd].empty()){ // 태울 수 있는 승객들을 태움
        int idx = q[nd].front();
        if(st[idx] > nt) break; // 아직 도착하지 않은 승객
        dt[idx] = nt + T;
        q[nd].pop();
        cnt++;
    }
}

void move(int *nd, int *nt){
    *nt = *nt + T;
    *nd = 1 - *nd;
}

void solve(){ // 각 손님들이 원하는 곳에 도착하게 되는 시간
    int nt=0; // 현재 시간
    int nd=0; // 현제 배의 위치 (0-left, 1-right)
    int cnt=0; // 현재 태운 승객 수
    while(!q[0].empty() || !q[1].empty()){ // 모두 이동할 때까지

        // 1. 당장 사람을 태울 수 있는 경우
        int idx = q[nd].front();
        if(!q[nd].empty() && st[idx] <= nt){
            ride(nd, nt); // 사람을 태움
            move(&nd, &nt); // 목적지에 데려다줌
        }

        // 2. 당장 사람을 태울 수 없는 경우
        else{
            if(q[1-nd].empty() || (!q[nd].empty() && q[nd].front()<=q[1-nd].front())) { // 현재 정박장에서 태우는 경우
                if(nt < st[idx]) nt = st[idx]; // 사람이 도착하기 까지 기다림
                ride(nd, nt); // 사람을 태움
                move(&nd, &nt); // 목적지에 데려다줌
            }
            else{ // 반대편 정박장에서 태우는 경우
                idx = q[1-nd].front();
                if(nt < st[idx]) nt = st[idx]; // 사람이 도착하기 까지 기다림
                move(&nd, &nt); // 반대 정박장으로 이동
                ride(nd, nt); // 사람을 태움
                move(&nd, &nt); // 목적지에 데려다줌
            }
        }
        
    }
}

void output(){ // 도착 시간 출력
    for(int idx=0; idx<N; idx++) cout << dt[idx] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}