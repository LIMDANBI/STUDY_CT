#include<iostream>
#include<string>
#include<queue>
#define MAX 1001
#define MAX2 1000001
#define MOD 10
using namespace std;

struct DATA{int num, cnt;};
queue<int> q;

int N, M;
int map[MAX][MAX];
DATA zero[MAX][MAX];

bool isused[MAX2];
bool visited[MAX][MAX];

int dy[] = {-1,1,0,0}; // 상하좌우
int dx[] = {0,0,-1,1};

void input(){
    cin >> N >> M;

    string line;
    for(int i=0; i<N; i++){
        cin >> line;
        for(int j=0; j<M; j++) map[i][j] = line[j]-'0';
    }
}

int check_zero_area(int y, int x){ // 이동 가능 영역 크기 반환
    visited[y][x] = true;
    int cnt = 1; // 이동 가능 영역 
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
        if(map[ny][nx] || visited[ny][nx]) continue;
        cnt+=check_zero_area(ny, nx);
    }
    return cnt;
}

void mark_zero_area(int y, int x, int num, int cnt){ // 이동 가능 영역 크기 표시
    zero[y][x] = {num, cnt};
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=M) continue;
        if(map[ny][nx] || zero[ny][nx].cnt) continue;
        mark_zero_area(ny, nx, num, cnt);
    }
}

void solution(){
    int num = 0; // group 번호
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            if(map[y][x]==0 && !visited[y][x]) {
                mark_zero_area(y, x, ++num, check_zero_area(y,x));
            }
        }
    }
}

void output(){
    int res, ny, nx;
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            if(map[y][x]){
                res = 1;
                for(int d=0; d<4; d++){ // 현위치를 기준으로 4 방향 확인
                    ny = y+dy[d];
                    nx = x+dx[d];
                    if(ny<0 || ny>=N || nx<0 || nx>=M || isused[zero[ny][nx].num]) continue; // 범위를 벗어나는 경우, 이미 체크한 영역인 경우
                    isused[zero[ny][nx].num] = true; // 영역 체크
                    q.push(zero[ny][nx].num);
                    res+=zero[ny][nx].cnt;
                } 
                while(!q.empty()){ // 다음에 사용하기 위해
                    isused[q.front()] = false;
                    q.pop();
                }
                cout << res%MOD; // 이동할 수 있는 칸의 개수를 10으로 나눈 나머지 출력
            }
            else cout << 0;
        }
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}