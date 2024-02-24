#include<iostream>
#define MAX 105
using namespace std;

string S;
int N, M;
char map[MAX][MAX];
int dy[] = {-1, 1, 0, 0, 1, 1, -1, -1};
int dx[] = {0, 0, -1, 1, 1, -1, 1, -1};

void input(){
    cin >> S;
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    }
}

bool check(int y, int x){

    // S의 길이
    int ssize = (int)S.size();

    // 상하좌우 대각선 확인
    for (int d = 0; d < 8; d++){
        
        bool res = true;
        int ny = y, nx = x;

        for (int i = 0; i < ssize; i++){
            if(ny<0 || nx>=N || nx<0 || nx>=M) res = false;
            if(map[ny][nx]!=S[i]) res = false;
            ny += dy[d]; nx += dx[d];
        }

        if(res) return true;
    }
    return false;
}

int solve(){

    // 각 지점에서 모두 확인
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if(!check(i, j)) continue;
            return 1;
        }
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}