#include<iostream>
#include<queue>
#define MAX 105
using namespace std;

struct DATA{int r, c, cnt;};

int N, M;
int R, C, S, K;
bool visited[MAX][MAX];
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {-1, -2, -2, -1, 1, 2, 2, 1};

void input(){
    cin >> N >> M;
    cin >> R >> C >> S >> K;
}

int solve(){
    queue<DATA> q;
    q.push({R, C, 0});
    visited[R][C] = true;

    while(!q.empty()){
        int r = q.front().r;
        int c = q.front().c;
        int cnt = q.front().cnt;
        q.pop();

        if(r==S && c==K) return cnt;
        for (int d = 0; d < 8; d++){
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(nr<1 || nr>N || nc<1 || nc>M || visited[nr][nc]) continue;
            visited[nr][nc] = true;
            q.push({nr, nc, cnt + 1});
        }
    }
    return -1; // for debugging
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}