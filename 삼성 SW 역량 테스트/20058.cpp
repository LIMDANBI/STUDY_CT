#include<iostream>
#include<vector>
#define MAX 65
using namespace std;

struct DATA{ int total, cnt;};

int n, N, Q;
int map[MAX][MAX];
int tmpMap[MAX][MAX];
bool visited[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int L[] = {1, 2, 4, 8, 16, 32, 64};

void rotate(int l){
    for (int r = 0; r < N; r+=l){
        for (int c = 0; c < N; c+=l){

            // 시계 방향으로 90도 회전
            for (int y = 0; y <l; y++){
                for (int x = 0; x < l; x++){
                    tmpMap[r + x][c + l - 1 - y] = map[r + y][c + x];
                }
            }

        }
    }

    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            map[r][c] = tmpMap[r][c];
            tmpMap[r][c] = 0;
        }
    }
}

void melt(){
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            if(!map[r][c]) continue; // 얼음이 없는 칸

            int cnt = 0;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr<0 || nr>=N || nc<0 || nc>=N || !map[nr][nc]) continue;
                cnt++;
            }
            if(cnt<3) tmpMap[r][c]--; // 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸
        }
    }

    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            map[r][c] += tmpMap[r][c];
            tmpMap[r][c] = 0;
        }
    }
}

DATA dfs(int r, int c){
    visited[r][c] = true;
    DATA res = {map[r][c], 1};
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(!map[nr][nc] || visited[nr][nc]) continue;
        DATA tmp = dfs(nr, nc);
        res.total += tmp.total;
        res.cnt += tmp.cnt;
    } return res;
}

void output(){
    int total = 0; // 남아있는 얼음의 합
    int maxCnt = 0; // 장 큰 덩어리가 차지하는 칸의 개수

     for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            if(!map[r][c] || visited[r][c]) continue;
            DATA res = dfs(r, c);
            total += res.total;
            maxCnt = max(res.cnt, maxCnt);
        }
    }

    cout << total << "\n";
    cout << maxCnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> Q; N = L[n];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    }

    while(Q--){
        int l; 
        cin >> l;
        rotate(L[l]);
        melt();
    }
    output();
}