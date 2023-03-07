#include<iostream>
#include<cstring>
#include<vector>
#define MAX 51
#define EMPTY 0
using namespace std;

struct POS{int y, x;};
vector<POS> cloud;

int N, M;
int map[MAX][MAX];
bool rained[MAX][MAX];
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1}; // ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void input(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void move_and_rain(int d, int s){
    memset(rained, false, sizeof(rained)); // init
    for(int i=0; i<cloud.size(); i++){
        int y = cloud[i].y;
        int x = cloud[i].x;
        y = (N*MAX + y + dy[d]*s)%N; // move
        x = (N*MAX + x + dx[d]*s)%N;
        cloud[i] = {y, x}; // update pos !!!
        map[y][x]++; // rain
        rained[y][x] = true;
    }
}

void water_copy_bug(){ // 물이 증가한 칸에 물복사버그 마법을 시전
    for(int i=0; i<cloud.size(); i++){
        int y = cloud[i].y;
        int x = cloud[i].x;
        
        int cnt = 0;
        for(int d=1; d<8; d+=2){ // 대각선 방향으로 거리가 1인 칸
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N || map[ny][nx]==EMPTY) continue;
            cnt++;
        }
        map[y][x]+=cnt;
    }
}

void form_cloud(){
    cloud.clear(); // 이전 구름 비워줌
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j] >= 2 && !rained[i][j]) {
                cloud.push_back({i,j});
                map[i][j]-=2;
            }
        }
    }
}

void output(){
    int ans = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) ans+=map[i][j];
    } cout << ans;
}

void solution(){
    
    // form cloud (initial)
    cloud.push_back({N-2, 0});
    cloud.push_back({N-2, 1});
    cloud.push_back({N-1, 0});
    cloud.push_back({N-1, 1});

    int d, s;
    while (M--){
        cin >> d >> s;
        move_and_rain(d-1, s);
        water_copy_bug();
        form_cloud();
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}