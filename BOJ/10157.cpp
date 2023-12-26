#include<iostream>
#include<vector>
#define pii pair < int, int>
using namespace std;

int C, R, K;
int dr[] = {1, 0, -1, 0}; // 상 우 하 좌
int dc[] = {0, 1, 0, -1};

void input(){
    cin >> C >> R;
    cin >> K;
}

pii solve(){
    if(C*R < K) return {0, 0}; // 좌석을 배정할 수 없는 경우

    int c = 1, r = 0;
    int ccnt = 0, rcnt = -1, order = 1;
    for (int d = 0; C - ccnt > 1; d++){
        d %= 4;            // 상우하좌 반복
        if(d==0 || d==2){  // 상하, r축
            rcnt++;
            for (int i = 0; i < R - rcnt; i++){
                r += dr[d];
                if(order++ == K) return {c, r};
            }
        }
        else{ // 좌우, c축
            ccnt++;
            for (int i = 0; i < C - ccnt; i++){
                c += dc[d];
                if(order++ == K) return {c, r};
            }
        }
    }
}

void output(pii res){
    if(res.first == 0) cout << 0;
    else cout << res.first << " " << res.second;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    output(solve());
}