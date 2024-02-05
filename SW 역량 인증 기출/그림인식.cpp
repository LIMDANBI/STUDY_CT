#include<iostream>
#define MAX 15
using namespace std;

int N; // 도화지 크기
int over[MAX];
char map[MAX][MAX]; // 도화지 색정보

void input(){
	cin >> N;
	for (int i = 0; i < N; i++) cin >> map[i];
}

void solve(){
    int ans = 0;

    for(int cnum=1; cnum<=9; cnum++){

        // 1. cnum 번호 색의 좌상단, 우하단을 구함
        int sy=MAX, sx=MAX, ey=0, ex=0; // 좌 상단, 우하단
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                if(map[y][x]-'0' != cnum) continue;
                sy = min(sy, y);
                sx = min(sx, x);
                ey = max(ey, y);
                ex = max(ex, x);
            }
        }

        if(sy == MAX) continue; // 해당 색이 없는 경우
        over[cnum]++;

        // 2. cnum 번호 색에 덧칠된 색을 찾음
        for(int y=sy; y<=ey; y++){
            for(int x=sx; x<=ex; x++){
                if(map[y][x]-'0' == cnum) continue;
                over[map[y][x]-'0']++;
            }
        }
    }

    for(int cnum=1; cnum<=9; cnum++){
        if(over[cnum] == 1) ans++;
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}