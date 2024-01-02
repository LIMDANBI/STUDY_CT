#include<iostream>
#include<queue>
#define MAX 105
#define INF 100001
using namespace std;

int N;
int cost[MAX][MAX];
int accum[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            char c; cin >> c;
            cost[i][j] = c - '0';
            accum[i][j] = INF; // init
        }
    }
}

void solve(){
    queue<pair<int, int>> q;
    accum[1][1] = 0;
    q.push({1, 1});

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<1 || ny>N || nx<1 || nx>N) continue;
            if(accum[y][x] + cost[ny][nx] < accum[ny][nx]){
                accum[ny][nx] = accum[y][x] + cost[ny][nx];
                q.push({ny, nx});
            }
        }
    }
    cout << accum[N][N];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}