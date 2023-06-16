#include<iostream>
#include<queue>
#define MAX 101
using namespace std;

struct DATA{ 
    int y, x, cnt;
    bool operator < (const DATA &D) const {
        return cnt > D.cnt;
    }
};

int N, M;
char map[MAX][MAX];
bool visited[MAX][MAX];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) cin >> map[i][j];
    }
}

int solution(){
    priority_queue<DATA> pq;
    pq.push({0, 0, 0});

    while(!pq.empty()){
        int y = pq.top().y;
        int x = pq.top().x;
        int cnt = pq.top().cnt;
        pq.pop();

        if(y == M-1 && x == N-1) return cnt;

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || ny>=M || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
            visited[ny][nx] = true;
            if(map[ny][nx] == '0') pq.push({ny, nx, cnt});
            else pq.push({ny, nx, cnt+1});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solution();
}