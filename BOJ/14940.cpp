#include<iostream>
#include<queue>
#define MAX 1001
using namespace std;

int N, M;
int y, x, c;
int map[MAX][MAX];
int dist[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
            dist[i][j] = map[i][j];
            if(map[i][j]==2){
                dist[i][j] = 0;
                y = i; x = j;
            }
            else if(map[i][j]==1) dist[i][j] = -1;
        }
    }
}

void solution(){
    queue<pair<int, int>> q;
    visited[y][x] = true;
    q.push({y, x});

    while (!q.empty()){
        y = q.front().first;
        x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
            if(visited[ny][nx] || map[ny][nx] == 0) continue;
            dist[ny][nx] = dist[y][x] + 1;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
}

void output(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++)
            cout << dist[i][j] << " ";
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}