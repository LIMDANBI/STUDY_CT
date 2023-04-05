// 걸린 시간 : 1h 19m
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 30
using namespace std;

struct POS {int y, x;};
struct GROUP {int y, x, num, cnt;};
vector<GROUP> group;

int N;
int gNum[MAX][MAX]; // 그룹 번호 저장
bool visited[MAX][MAX];
int map[MAX][MAX], tmpMap[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++) cin >> map[y][x];
    }
}

int dfs(int y, int x, int num, int gnum){
    visited[y][x] = true;
    gNum[y][x] = gnum;

    int res = 1;
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=N) continue; // 범위를 벗어나는 경우
        if(visited[ny][nx] || map[ny][nx]!=num) continue; // 이미 방문한 경우, 다른 숫자인 경우
        res += dfs(ny, nx, num, gnum);
    }
    return res;
}

void get_group(){
    memset(visited, false, sizeof(visited)); // init

    int gnum = 0;
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            if(visited[y][x]) continue;
            int cnt = dfs(y, x, map[y][x], gnum++);
            group.push_back({y, x, map[y][x], cnt});
        }
    }
}

int bfs(int a, int b){ // 그룹 a, b의 맞닿은 변의 수를 반환

    memset(visited, false, sizeof(visited)); // init

    int res = 0;
    int ay = group[a].y;
    int ax = group[a].x;
    
    queue<POS> q;
    q.push({ay, ax});
    visited[ay][ax] = true;

    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x;
        q.pop();

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어나는 경우
            if(gNum[ny][nx] == b) res++; // 맞 닿은 변
            if(gNum[ny][nx] == a){
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
    return res;
}

int cal_score(){
    int res = 0;
    for (int a = 0; a < (int)group.size() - 1; a++){
        for (int b = a+1; b < (int)group.size(); b++){
            int scoreAB = (group[a].cnt + group[b].cnt) * group[a].num * group[b].num * bfs(a, b);
            res += scoreAB;
        }
    }
    return res;
}

void clock_wise(int y, int x){
    int mid = N / 2;
    for (int r = 0; r < mid; r++){
        for (int c = 0; c < mid; c++)
            tmpMap[y + c][x + mid - 1 - r] = map[y + r][x + c];
    }
}

void rotate_map(){
    
    int mid = N / 2;

    tmpMap[mid][mid] = map[mid][mid];

    // 십자가 반시계 90'
    for (int c = 0; c < mid; c++) tmpMap[mid][c] = map[c][mid];
    for (int r = 0; r < mid; r++) tmpMap[r][mid] = map[mid][N - 1 - r];
    for (int c = N-1; c > mid; c--) tmpMap[mid][c] = map[c][mid];
    for (int r = N-1; r > mid; r--) tmpMap[r][mid] = map[mid][N - 1 - r];

    // 정사각형 시계 90'
    clock_wise(0, 0);
    clock_wise(0, mid + 1);
    clock_wise(mid + 1, 0);
    clock_wise(mid + 1, mid + 1);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            map[i][j] = tmpMap[i][j];
            tmpMap[i][j] = 0; // init
        }
    }
}

void solution(){
    int ans = 0;
    for (int turn = 0; turn < 4; turn++) {
        group.clear();                     // init
        get_group();                       // 그룹을 구함
        ans += cal_score();                // 예술 점수 계산
        rotate_map();                      // 회전
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}