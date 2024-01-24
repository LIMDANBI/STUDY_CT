#include<iostream>
#define MAX 102
using namespace std;

int N;
bool map[MAX][MAX];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void attach(int x, int y){
    for(int i=x; i<x+10; i++){
        for(int j=y; j<y+10; j++) map[i][j] = true;
    }
}

int getRound(){
    int res = 0;
    for(int x=1; x<MAX-1; x++){
        for(int y=1; y<MAX-1; y++){
            if(!map[x][y]) continue;
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(!map[nx][ny]) res++;
            }
        }
    }
    return res;
}

void solve(){
    cin >> N;
    
    int x, y;
    while(N--){
        cin >> x >> y;
        attach(x, y);
    }
    cout << getRound();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}