#include<iostream>
#define MAX 25
using namespace std;

int N, M, ans=10001;
int order[MAX], openDoorIdx[2];

void input(){
    cin >> N;
    cin >> openDoorIdx[0] >> openDoorIdx[1];
    cin >> M;
    for(int i=1; i<=M; i++) cin >> order[i];
}

void solve(int m, int move){
    if(ans < move) return; // 더 작게 이동하는 방법을 이미 알고 있음
    if(m == M+1){
        ans = min(ans, move);
        return;
    }

    if(openDoorIdx[0] > openDoorIdx[1]) { // openDoorIdx[0]이 openDoorIdx[1]보다 작음을 보장
        int tmp = openDoorIdx[0];
        openDoorIdx[0] = openDoorIdx[1];
        openDoorIdx[1] = tmp;
    }

    if(order[m] < openDoorIdx[0] && order[m] < openDoorIdx[1]){ // use open1 open2
        int tmp = openDoorIdx[0];
        openDoorIdx[0] = order[m];
        solve(m+1, move+tmp-order[m]);
        openDoorIdx[0] = tmp;
    }
    else if(order[m] > openDoorIdx[0] && order[m] > openDoorIdx[1]){ // open1 open2 use
        int tmp = openDoorIdx[1];
        openDoorIdx[1] = order[m];
        solve(m+1, move+order[m]-tmp);
        openDoorIdx[1] = tmp;
    }
    else{ // open1 use open2
        int tmp = openDoorIdx[0];
        openDoorIdx[0] = order[m];
        solve(m+1, move+order[m]-tmp);
        openDoorIdx[0] = tmp;

        tmp = openDoorIdx[1];
        openDoorIdx[1] = order[m];
        solve(m+1, move+tmp-order[m]);
        openDoorIdx[1] = tmp;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve(1, 0);
    cout << ans;
}