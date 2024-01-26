#include<iostream>
#include<vector>
#define MAX 100
using namespace std;

struct POS{int x, y;};

int N;
vector<POS> edge;
bool map[MAX][MAX];

void paint(int x, int y){
    for(int i=x; i<x+10; i++){
        for(int j=y; j<y+10; j++) map[i][j] = true;
    }
}

bool isPossible(int sx, int sy, int ex, int ey){
    for(int x=sx; x<=ex; x++){
        for(int y=sy; y<=ey; y++){
            if(!map[x][y]) return false;
        }
    }
    return true;
}

void solve(){

    cin >> N;

    // 1. 색종이 붙이기
    int x, y;
    for(int i=0; i<N; i++){
        cin >> x >> y;
        paint(x, y);
    }

    // 2. 최대 면적 구하기
    int ans = 100;
    for(int sx=0; sx<MAX-1; sx++){
        for(int sy=0; sy<MAX-1; sy++){
            if(!map[sx][sy]) continue; // 빈칸
            for(int ex=sx+1; ex<MAX; ex++){
                for(int ey=sy+1; ey<MAX; ey++){
                    if(!map[ex][ey]) break; // 빈칸
                    int val = (ex-sx+1)*(ey-sy+1); // 확인할 영역 넓이
                    if(val <= ans || !isPossible(sx, sy, ex, ey)) continue;
                    ans = max(ans, val);
                }
            }
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}