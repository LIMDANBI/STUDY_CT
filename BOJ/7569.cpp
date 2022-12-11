#include<iostream>
#include<queue>
#define MAX 101
using namespace std;

struct DATA{int h, n, m, day;};
queue<DATA> q;

int tomato = 0;
int M, N, H; // n x m x h
int storage[MAX][MAX][MAX];
bool visited[MAX][MAX][MAX];

// 위, 아래, 왼쪽, 오른쪽, 앞, 뒤
int dn[] = {0, 0, 0, 0, -1, 1};
int dm[] = {0, 0, -1, 1, 0, 0};
int dh[] = {-1, 1, 0, 0, 0, 0};

void input(){
    cin >> M >> N >> H;
    for(int i=0; i<H; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                cin >> storage[i][j][k];
                if(storage[i][j][k]==0) tomato++;
                else if(storage[i][j][k]==1) {
                    q.push({i,j,k,0});
                    visited[i][j][k] = true;
                }
            }
        }
    }
}

void solution(){ // 토마토가 모두 익을 때까지 최소 며칠이 걸리는지

    int ans = 0;
    while(!q.empty()){
        int n = q.front().n;
        int m = q.front().m;
        int h = q.front().h;
        int day = q.front().day;
        q.pop();

        for(int d=0; d<6; d++){
            int nn = n+dn[d];
            int nm = m+dm[d];
            int nh = h+dh[d];
            if(nn<0 || nn >= N || nm<0 || nm>=M || nh<0 || nh>=H || visited[nh][nn][nm]) continue;
            if(storage[nh][nn][nm] == 0){
                visited[nh][nn][nm] = true;
                q.push({nh, nn, nm, day+1});
                ans = max(ans, day+1);
                tomato--;
            }
        }
    }
    if(tomato == 0) cout << ans;
    else cout << -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}