#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

int N, ans = 0;
int map[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
vector<pair<int, int> > wormhole[11];

int NDIR[6][4] = { // (블록 번호, 현재 방향) 일 때 다음 방향
    {0, 0, 0, 0},
    {1, 3, 0, 2}, // 1번 block
    {3, 0, 1, 2}, // 2번 block
    {2, 0, 3, 1}, // 3번 block
    {1, 2, 3, 0}, // 4번 block
    {1, 0, 3, 2}, // 5번 block
};

void init(){
    ans = 0;
    for (int i = 6; i < 11; i++) wormhole[i].clear();
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if(map[i][j]==0 || map[i][j]==-1) continue;
            wormhole[map[i][j]].push_back({i, j});
        }
    }
}

int get_score(int y, int x, int d){
    int sy = y, sx = x, score=0; // 시작 좌표, 획득 점수

    while (true) { // 공 이동 (시뮬레이션)
        y += dy[d]; x += dx[d]; // move
        if(y<0 || y>=N || x<0 || x>=N){ // 벽에 부딪힌 경우
            score++;
            y -= dy[d]; x -= dx[d]; // 원위치
            d==0 || d==2 ? d++ : d--; // 방향 바꿔주기
        }
        if((y==sy && x==sx) || map[y][x]==-1) return score; // 시작점으로 돌아오거나, 블랙홀인 경우
        if(map[y][x]==0) continue; // 빈칸인 경우
        if(map[y][x]<6){ // 블록에 부딪힌 경우
            score++; // 점수 획득
            d = NDIR[map[y][x]][d];
        }
        else{ // 웜홀인 경우
            int num = map[y][x]; // 웜홀 번호
            if(y==wormhole[num][0].first && x==wormhole[num][0].second) {
                y = wormhole[num][1].first;
                x = wormhole[num][1].second;
            }
            else{
                y = wormhole[num][0].first;
                x = wormhole[num][0].second;
            }
        }
    }
}

void solution(){
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            if(map[y][x]!=0) continue;
            for (int d = 0; d < 4; d++) ans = max(ans, get_score(y, x, d));
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        init();
        input();
        solution();
        cout << "#" << t << " " << ans << "\n";
    }
}