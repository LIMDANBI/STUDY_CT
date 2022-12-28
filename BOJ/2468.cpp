#include<iostream>
#include<cstring>
#define MAX 101
using namespace std;

int N, max_val;
int arr[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            cin >> arr[i][j];
            max_val = max(max_val, arr[i][j]);
        }
    }
}

void dfs(int y, int x, int rain){
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(!visited[ny][nx] && arr[ny][nx] > rain) dfs(ny, nx, rain);
    }
}

void solution(){

    int ans = 1;

    for(int rain=1; rain<max_val; rain++){

        int res = 0;
        memset(visited, false, sizeof(visited));
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(!visited[i][j] && arr[i][j] > rain) {
                    dfs(i, j, rain);
                    res++;
                }
            }
        }
        ans = max(ans, res);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}