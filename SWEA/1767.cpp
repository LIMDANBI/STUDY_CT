#include<iostream>
#include<vector>
#define MAX 12
using namespace std;

int N;
bool map[MAX][MAX];
vector<pair<int, int>> cores;
int sumOfLine, connCore, maxCore;

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init(){
    maxCore = 0;  // 전선 길의 합
    connCore = 0; // 연결된 core
    sumOfLine = 0; // 최대 연결 가능한 core
    cores.clear();
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if(map[i][j]){ // core인 경우
                if(i==0 || i==N-1 || j==0 || j==N-1) connCore++;
                else cores.push_back({i, j});
            }
        }
    } maxCore = connCore;
}

void solution(int cnt, int core, int len){
    if(cnt == cores.size()){
        if(core == maxCore) sumOfLine = min(sumOfLine, len);
        else if(maxCore < core){
            maxCore = core;
            sumOfLine = len;
        }
        return ;
    }

    // 미연결
    solution(cnt + 1, core, len);

    // 연결 (가능한 경우 - 상,하,좌,우)
    for (int d = 0; d < 4; d++){

        int l = 0;
        bool flag = true;

        int y = cores[cnt].first;
        int x = cores[cnt].second;

        while(true){
            y += dy[d];
            x += dx[d];
            if(y<0 || y>=N || x<0 || x>=N) break;
            if(map[y][x]) {flag=false; break;}
            map[y][x] = true; l++;
        }

        if(flag) solution(cnt + 1, core + 1, len + l);

        // 복구 
        while(l--){
            y -= dy[d];
            x -= dx[d];
            map[y][x] = false;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        init();
        input();
        solution(0, connCore, 0);
        cout << "#" << t << " " << sumOfLine << "\n";
    }
}