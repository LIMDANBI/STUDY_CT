#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 51
using namespace std;

struct DATA{int r, c, dist;};

int R, C, ans;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
vector<pair<int, int> > pos;


void input(){
    cin >> R >> C;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            cin >> map[i][j];
            if(map[i][j]=='L') pos.push_back({i, j});
        }
    }
}

void dfs(int r, int c, int dist){
    ans = max(ans, dist);
    visited[r][c] = true;
    for (int d = 0; d < 4; d++){
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(nr<0 || nr>=R || nc<0 || nc>=C) continue;
        if(visited[nr][nc] || map[nr][nc]=='W') continue;
        dfs(nr, nc, dist + 1);
    }
}

void solution(){
    for (int i = 0; i < (int)pos.size(); i++){
        int r = pos[i].first, c = pos[i].second, dist;
        memset(visited, false, sizeof(visited));

        queue<DATA> q;
        q.push({r, c, 0});
        visited[r][c] = true;

        while (!q.empty()){
            r = q.front().r;
            c = q.front().c;
            dist = q.front().dist;
            ans = max(ans, dist);
            q.pop();

            for (int d = 0; d < 4; d++){
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr<0 || nr>=R || nc<0 || nc>=C) continue;
                if(visited[nr][nc] || map[nr][nc]=='W') continue;
                q.push({nr, nc, dist + 1});
                visited[nr][nc] = true;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    cout << ans;
}