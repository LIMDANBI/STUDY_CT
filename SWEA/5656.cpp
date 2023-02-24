#include<iostream>
#include<cstring>
#include<queue>
#define EMPTY 0
#define MAX_W 13
#define MAX_H 16
#define INF 10001
using namespace std;

int ans;
int N, W, H; // // 쏠 기회, H x W 배열
int map[MAX_H][MAX_W];
bool visited[MAX_H][MAX_W];
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

void input(){
    cin >> N >> W >> H;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++) cin >> map[i][j];
    }
}

void break_brick(int h, int w){
    memset(visited, false, sizeof(visited)); // 방문 여부 초기화 
    queue<pair<int, int>> q;
    visited[h][w] = true;
    q.push({h, w});

    while(!q.empty()){
        h = q.front().first;
        w = q.front().second;
        int cnt = map[h][w];
        map[h][w] = EMPTY; // 벽돌 깨기
        q.pop();

        for(int d=0; d<4; d++){
            int nh = h, nw = w;
            for(int k=1; k<cnt; k++){ // 벽돌에 적힌 숫자 = 제거되는 범위
                nh+=dh[d]; nw+=dw[d];
                if(nh<0 || nh>=H || nw<0 || nw>=W) break; // 범위를 벗어나는 경우
                if(visited[nh][nw] || map[nh][nw] == EMPTY) continue; // 이미 방문한 경우, 벽돌이 없는 경우
                visited[nh][nw] = true;
                q.push({nh, nw});
            }
        }
    }
}

void drop_brick(){ // 빈 공간이 있을 경우 벽돌은 밑으로 떨어짐
    for(int w=0; w<W; w++){
        queue<int> q;
        for(int h=H-1; h>=0; h--){
            if(map[h][w]) {
                q.push(map[h][w]);
                map[h][w] = EMPTY;
            }
        }

        int h = H-1;
        while(!q.empty()){
            map[h--][w] = q.front();
            q.pop();
        }
    }
}

int get_remain_brick(){ // 남은 벽돌의 개수
    int res = 0;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++) {
            if(map[i][j]) res++;
        }
    } return res;
}

void solution(int cnt){ // N 개의 구슬을 떨어트려 최대한 많은 벽돌을 제거
    if(cnt == N){
        ans = min(ans, get_remain_brick());
        return ; 
    }

     // 배열 복사
    int copy_map[MAX_H][MAX_W];
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++) copy_map[i][j] = map[i][j];
    }

    for(int w=0; w<W; w++){
        for(int h=0; h<H; h++){
            if(map[h][w] == EMPTY) continue;
            break_brick(h, w); // 구슬 쏘기
            drop_brick(); // 벽돌이 밑으로 떨어짐
            solution(cnt+1);

            // 배열 복구
            for(int i=0; i<H; i++){
                for(int j=0; j<W; j++) map[i][j] = copy_map[i][j];
            }
            break; // 가장 위에 있는 벽돌만 깰 수 있음
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        ans=INF; // init
        input();
        solution(0);
        if(ans == INF) ans = 0;
        cout << "#" << t << " " << ans << "\n";
    }
}