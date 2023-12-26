#include<iostream>
#include<queue>
#define MAX 105
using namespace std;

int W, H;
int sw, sh, ew, eh;
int cost[MAX][MAX]; // 소요 시간
char maze[MAX][MAX];
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

void input(){
    cin >> W >> H;
    cin >> sw >> sh >> ew >> eh;
    for(int h=1; h<=H; h++){
        for(int w=1; w<=W; w++) cin >> maze[h][w];
    }
}

int solve(){
    queue<pair<int, int> > q;
    cost[sh][sw] = 1;
    q.push({sh, sw});

    while(!q.empty()){
        int h = q.front().first;
        int w = q.front().second;
        q.pop();

        if(h==eh && w==ew) return cost[h][w] - 1;
        for(int d=0; d<4; d++){
            int nh = h+dh[d];
            int nw = w+dw[d];
            if(nh<1 || nh>H || nw<1 || nw>W) continue; 
            if(cost[nh][nw] || maze[nh][nw]=='1') continue;
            cost[nh][nw] = cost[h][w] + 1;
            q.push({nh, nw});
        }
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solve();
}