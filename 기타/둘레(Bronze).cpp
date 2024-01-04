#include<iostream>
#define MAX 102
using namespace std;

int N, r, c;
bool hay[MAX][MAX];
bool outdoor[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> r >> c;
        hay[r][c] = true; // 건초
    }
}

void check_outdoor(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX && !hay[i][j]; j++) outdoor[i][j] = true;
        for(int j=MAX-1; j>=0 && !hay[i][j]; j--) outdoor[i][j] = true;
    }
}

void get_boundary(){
    int ans = 0;
    for(int y=1; y<MAX-1; y++){
        for(int x=1; x<MAX-1; x++){
            if(!hay[y][x]) continue;
            for(int d=0; d<4; d++){
                int ny = y+dy[d];
                int nx = x+dx[d];
                if(outdoor[ny][nx]) ans++;
            }
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    check_outdoor();
    get_boundary();
}