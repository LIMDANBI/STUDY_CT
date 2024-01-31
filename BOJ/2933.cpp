#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 101
using namespace std;

struct POS{int y, x;};
vector<POS> cluster;

int R, C, N;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> R >> C;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++)
            cin >> map[i][j];
    }
    cin >> N;
}

void throwStick(int y, int d){
    int x;
    if(d == 0){ // 왼쪽에서 던짐 (창영)
        x = 0;
        while(x<C && map[y][x]!='x') x++;
    }
    else{ // 오른쪽에서 던짐 (상근)
        x = C - 1;
        while(x>=0 && map[y][x]!='x') x--;
    }

    // 미네랄 파괴
    if(0<=x && x<C) map[y][x] = '.';
}

bool dfs(int y, int x, bool issave){

    bool res = true;

    // 1. 중력이 작용할 수 없는 경우
    if(y == R-1) return false;

    // 2. 방문
    visited[y][x] = true;
    if(issave) cluster.push_back({y, x});
    
    // 3. 다음 방문점 찾기
    for (int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny<0 || ny>=R || nx<0 || nx>=C) continue;
        if(map[ny][nx]!='x' || visited[ny][nx]) continue;
        if(!dfs(ny, nx, issave)) res = false;
    }

    return res;
}

bool findCluster(){

    bool res = false;

    // 1. 초기화
    cluster.clear();
    memset(visited, false, sizeof(visited));

    // 2. 중력이 작용할 클러스터를 찾음
    int y, x;
    for (int i = 0; i < R && !res; i++){
        for (int j = 0; j < C; j++){
            if(map[i][j]!='x' || visited[i][j]) continue;
            if(dfs(i, j, false)) {
                y = i; x = j;
                res = true;
                break;
            }
        }
    }

    // 3. 중력이 작용할 클러스터의 위치 저장
    if(res) {
        memset(visited, false, sizeof(visited));
        dfs(y, x, true);
    }

    return res;
}

void gravity(){
    
    // 1. 중력이 작용할 클러스터를 찾음
    if(!findCluster()) return;
    for(auto p : cluster)
        map[p.y][p.x] = '.';

    // 2. 중력 작용 가능한 cnt를 찾음 (몇칸 떨어질 수 있는지)
    int cnt = 0;
    bool iscontinue = true;
    while (iscontinue){
        cnt++;
        for(auto p : cluster){
            if(p.y+cnt>=R || map[p.y+cnt][p.x]=='x') {
                iscontinue = false;
                cnt--;
                break;
            }
        }
    }

    // 3. 중력 작용
    for(auto p : cluster)
        map[p.y+cnt][p.x] = 'x';
}

void solve(){
    int h, turn = 0; // 창영(0), 상근(1)
    while (N--){
        cin >> h;

        // 1. 막대를 던짐
        throwStick(R-h, turn);

        // 2. 중력 작용
        gravity();

        // 3. 턴 변경
        turn = 1 - turn;
    }
}

void output(){
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++)
            cout << map[i][j];
        cout << " \n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}