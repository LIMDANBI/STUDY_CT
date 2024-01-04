#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 30
using namespace std;

int N;
vector<int> v;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

int dfs(int y, int x){
    int res = 1;
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny >=N || nx<0 || nx>=N) continue;
        if(map[ny][nx]=='0' || visited[ny][nx]) continue;
        res += dfs(ny, nx);
    }
    return res;
}

void solve(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j]=='0' || visited[i][j]) continue;
            v.push_back(dfs(i, j));
        }
    }
}

void output(){
    cout << v.size() << "\n";
    sort(v.begin(), v.end());
    for(int i=0; i<v.size(); i++) cout << v[i] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}