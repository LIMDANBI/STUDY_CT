#include<iostream>
#include<queue>
#define MAX 105
using namespace std;

struct POS{int r, c;};

int R, C;
int sr, sc, cnt;
bool map[MAX][MAX];
int dtime[MAX][MAX];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

void init(){
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++) dtime[i][j] = -1;
    }
}

void input(){
    cin >> C >> R;
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            char c; cin >> c;
            map[i][j] = c -'0';
            if(map[i][j]) cnt++; // 저글링 수
        }
    }
    cin >> sc >> sr;
}

void solve(){
    int t = 3; // 죽을 수 있는 저글링들이 모두 죽을 때까지 걸리는 초
    int n = 0; // 죽은 저글링 수

    // 1. 방사능 오염 시작점 처리
    queue<POS> q;
    q.push({sr, sc});
    dtime[sr][sc] = 3;

    // 2. bfs
    while(!q.empty()){
        int r = q.front().r;
        int c = q.front().c;
        q.pop();
        n++;
        
        // 1초마다 이웃한 저글링에 오염
        for(int d=0; d<4; d++){
            int nr = r+dr[d];
            int nc = c+dc[d];
            if(nr<1 || nr>R || nc<1 || nc>C) continue; // 범위를 벗어나는 경우
            if(dtime[nr][nc]>0 || !map[nr][nc]) continue; // 이미 방문했거나 저글링이 아닌 경우
            dtime[nr][nc] = dtime[r][c]+1; // 오염된 시간
            t = max(t, dtime[nr][nc]);
            q.push({nr, nc});
        }
    }
    cout << t << "\n" << cnt-n;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solve();
}