#include <iostream>
#include <vector>
#include <queue>
#define MAX 11
#define pii pair<int, int>
using namespace std;

struct RUNNER{
    int r, c;
    bool isEixt = false;
};
vector<RUNNER> runners;

int N, M, K;
int er, ec;
int exitCnt; // 탈출자 수
int moveCnt; // 이동거리 합
int map[MAX][MAX];
int dr[] = {-1,1,0,0}; // 상하좌우
int dc[] = {0,0,-1,1};

// void print_map(){
//     for(int r=1; r<=N; r++){
//         for(int c=1; c<=N; c++) cout << map[r][c] << " ";
//         cout << "\n";
//     }
// }

// void pirnt_runner(){
//     cout << "here runner\n";
//     for(auto runner : runners){
//         if(runner.isEixt) continue;
//         cout << runner.r << " " << runner.c << "\n";
//     }
//     cout << "runner end\n";
// }

void input(){
    cin >> N >> M >> K;
    for(int r=1; r<=N; r++){ // 미로
        for(int c=1; c<=N; c++) cin >> map[r][c];
    }
    for(int m=0; m<M; m++){ // 참가자
        int r, c;
        cin >> r >> c;
        runners.push_back({r, c, false});
    }
    cin >> er >> ec; // 출구
}

void move(){
    for(int i=0; i<runners.size(); i++){
        if(runners[i].isEixt) continue; // 이미 탈출한 참가자

        int r = runners[i].r;
        int c = runners[i].c;
        int dist = abs(r-er) + abs(c-ec);

        priority_queue<pii, vector<pii>, greater<pii>> pq; // dist, d

        for(int d=0; d<4; d++){
            int nr = r+dr[d];
            int nc = c+dc[d];
            int new_dist = abs(nr-er) + abs(nc-ec);
            if(nr<1 || nr>N || nc<1 || nc>N) continue;
            if(new_dist < dist && map[nr][nc]==0) {
                // cout  << nr << " " << nc << " " << new_dist << " " << d << " nr nc nd d \n";
                pq.push({new_dist, d});
            }
        }

        if(!pq.empty()){ // 움직이는 경우
            moveCnt++;
            int d = pq.top().second; 
            // cout << d << " is d \n";
            runners[i] = {r+dr[d], c+dc[d], false};
            if(runners[i].r == er && runners[i].c == ec) {
                runners[i].isEixt = true;
                exitCnt++;
            }
        }
    }
}

bool isfind(int k, int r, int c){
    if(r+k>N || c+k>N) return false; // 범위 확인
    if(!(r<=er && er<=r+k && c<=ec && ec<=c+k)) return false; // 출구 포함 확인
    for(auto runner : runners){ // runner 포함 확인
        if(runner.isEixt) continue;
        if(r<=runner.r && runner.r<=r+k && c<=runner.c && runner.c<=c+k) return true;
    }
    return false;
}

void rotate(){ // 참가자 최소 1명을 포함한 가장 작은 정사각형을 시계 방향으로 회전
    
    for(int k=1; k<N; k++){ // 정사각형 길이
        for(int r=1; r<N; r++){
            for(int c=1; c<N; c++){
                if(isfind(k, r, c)){

                    int tmp[k+1][k+1];

                    // 시계 방향 회전
                    for(int y=0; y<k+1; y++){
                        for(int x=0; x<k+1; x++){
                            tmp[y][x] = max(0, map[r+k-x][c+y]-1); // 내구도 1 감소
                        }
                    }
                    for(int y=0; y<k+1; y++){
                        for(int x=0; x<k+1; x++){
                            map[r+y][c+x] = tmp[y][x];
                        } 
                    } 
                    // print_map(); exit(0);
                    
                    // 출구 (er, ec) 변경
                    int y = er - r;
                    int x = ec - c;
                    er = r + x;
                    ec = c + k - y;

                    // 정사각형에 포함된 runner 변경
                    for(int i=0; i<runners.size(); i++){
                        if(runners[i].isEixt) continue;
                        if(r<=runners[i].r && runners[i].r<=r+k && c<=runners[i].c && runners[i].c<=c+k){ // 범위에 포함되는 경우
                            y = runners[i].r - r;
                            x = runners[i].c - c;
                            runners[i] = { r + x, c + k - y, false};
                        }
                    }
                    return;
                }
            }
        }
    }
}

int main() {
    input();
    while(K--){
        move();
        if(exitCnt == M) break;
        rotate();
    }
    cout << moveCnt << "\n";
    cout << er << " " << ec;
}