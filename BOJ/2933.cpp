#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 101
using namespace std;

priority_queue<pair<int, int> > tmp_move, need_move;

int R, C, N;
bool map[MAX][MAX];
bool tmpMap[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> R >> C;

    char c;
    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++) {
            cin >> c;
            if(c == 'x') map[i][j] = true;
        }
    }
}

int find_col(int dir, int row){
    if (dir%2 == 1) { // left to right
        int col = 0;
        while(++col <= C){
            if(map[row][col]) return col;
        }
    }
    else{ // right to left
        int col = C+1;
        while(--col >= 1){
            if(map[row][col]) return col;
        }
    }
    return -1;
}

void find_clust_and_point(int y, int x){
    visited[y][x] = true;
    tmp_move.push({y,x});
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<1 || ny>R || nx<1 || nx>C) continue;
        if(visited[ny][nx] || !map[ny][nx]) continue;
        find_clust_and_point(ny, nx);
    }
}

int get_need_cnt(){
    int min_cnt = R - tmp_move.top().first;

    while(!tmp_move.empty()){
        int r = tmp_move.top().first;
        int c = tmp_move.top().second;
        need_move.push(tmp_move.top());
        tmp_move.pop();

        int cnt = 0;
        while(++r<=R){
            if(map[r][c] && !visited[r][c]) {
                min_cnt = min(min_cnt, cnt);
                break;
            }
            cnt++;
        }
    }
    return min_cnt;
}

void gravity(int r, int c){
    memset(visited, false, sizeof(visited)); // init

    vector<pair<int, int> > v;
    for (int d = 0; d < 4; d++){
        int nr = r + dy[d];
        int nc = c + dx[d];
        if(nr<1 || nr>R || nc<1 || nc>C || !map[nr][nc]) continue;
        v.push_back({nr, nc});
    }

    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++) tmpMap[i][j] = map[i][j];
    }

    for (int i = 0; i < (int) v.size(); i++){
        int y = v[i].first, x = v[i].second;
        if(!visited[y][x]) {
            find_clust_and_point(y, x); // 클러스터와 기준점을 찾음
            int cnt = get_need_cnt();
            while(!need_move.empty()){
                r = need_move.top().first;
                c = need_move.top().second;
                need_move.pop();
                tmpMap[r][c] = false;
                tmpMap[r + cnt][c] = true;
            }
        }
    }

    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++) map[i][j] = tmpMap[i][j];
    }
}

void solution(){
    cin >> N;

    int col, row;
    for (int i = 1; i <= N; i++){
        cin >> row; row = R-row+1;
        col = find_col(i, row);
        if(col==-1) continue; // 미네랄이 없는 경우
        map[row][col] = false; // 미네랄 파괴
        gravity(row, col); // 중력 작용
    }
}

void output(){
    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++)
            map[i][j] ? cout << "x" : cout << ".";
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}