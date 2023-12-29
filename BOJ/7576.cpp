#include <iostream>
#include <queue>
#define MAX 1005
using namespace std;

struct DATA{int y, x, day;};
queue<DATA> q;

int N, M;
int need; // 익어야하는 토마토
int box[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            cin >> box[i][j];
            if(box[i][j] == 0) need++; // 익지 않은 토마토
            else if(box[i][j] == 1) { // 익은 토마토
                q.push({i, j, 0});
                visited[i][j] = true;
            }
        }
    }
}

int solve(){
    if(need == 0) return 0;
    while (!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        int day = q.front().day;
        q.pop();

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || ny>=M || nx<0 || nx>=N) continue; // 범위를 벗어나는 경우
            if(visited[ny][nx] || box[ny][nx]==-1) continue; // 이미 방문했거나, 토마토가 들어있지 않은 경우
            if(--need == 0) return day+1; // 토마토가 모두 익을 때까지의 최소 날
            q.push({ny, nx, day + 1});
            visited[ny][nx] = true;
        }
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}