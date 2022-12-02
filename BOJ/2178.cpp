#include<iostream>
#include<queue>
#define MAX 101
#define INF 987654321
using namespace std;

int N, M;
int maze[MAX][MAX];
int dist[MAX][MAX];
int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

void input(){
    cin >> N >> M;

    string str;
    for(int i=1; i<=N; i++){
        cin >> str;
        for(int j=1; j<=M; j++) {
            maze[i][j] = str[j-1]-'0';
            dist[i][j] = INF;
        }
    }
}

void solution(){
    queue<pair<int, int>> q;
    q.push({1, 1});
    dist[1][1] = 1;

    while (!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int d=0; d<4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<1 || ny>N ||nx<1 || nx>M) continue;
            if(maze[ny][nx]==0 || dist[ny][nx]!=INF) continue;
            dist[ny][nx] = dist[y][x]+1;
            q.push({ny,nx});
        }
    }
    cout << dist[N][M]; 
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}