#include<iostream>
#define MAX 500
#define SPACE 9
#define EMPTY 0
using namespace std;

int N;
int map[MAX][MAX];
int dy[] = {0, 1, 0, -1}; // 좌 하 우 상
int dx[] = {-1, 0, 1, 0};
int Ratio[] = {1, 1, 2, 2, 5, 7, 7, 10, 10};
int sy[4][SPACE] = {
    {-1, 1, -2, 2, 0, -1, 1, -1, 1},
    {-1, -1, 0, 0, 2, 0, 0, 1, 1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1},
    {1, 1, 0, 0, -2, 0, 0, -1, -1}
};
int sx[4][SPACE] = {
    {1, 1, 0, 0, -2, 0, 0, -1, -1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1},
    {-1, -1, 0, 0, 2, 0, 0, 1, 1},
    {-1, 1, -2, 2, 0, -1, 1, -1, 1}
};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

int sand_scattered(int y, int x, int d){
    int res=0; // 격자의 밖으로 나간 모래의 양
    int now = map[y][x];
    for(int s=0; s<SPACE; s++){
        int ny = y+sy[d][s];
        int nx = x+sx[d][s];
        int cnt = now*Ratio[s]/100;
        map[y][x]-=cnt;
        if(ny<0 || ny>=N || nx<0 || nx>=N) res+=cnt;
        else map[ny][nx]+=cnt;
    }

    // 남은 모래 이동 a
    int ny=y+dy[d], nx=x+dx[d]; 
    if(ny<0 || ny>=N || nx<0 || nx>=N) res+=map[y][x]; // 범위 벗어나는지 확인 
    else map[ny][nx] += map[y][x];
    map[y][x] = EMPTY;
    return res;
}

void solution(){
    int ans = 0;
    int y=N/2, x=N/2, cnt = 0;
    for(int d=0; x!=-1; d++){ d%=4;
        if(d%2==0) cnt++;
        for(int c=0; c<cnt; c++){
            y+=dy[d];
            x+=dx[d];
            if(x==-1) break;
            if(map[y][x]!=EMPTY) ans+=sand_scattered(y, x, d);
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}