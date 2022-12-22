#include<iostream>
#include<queue>
#define INF 987654321
#define MAX 126
using namespace std;

int N;
int arr[MAX][MAX];
int cost[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) {
            cin >> arr[i][j];
            cost[i][j] = INF;
        }
    }
}

int solution(){
    
    queue<pair<int, int>> q;
    cost[0][0] = arr[0][0];
    q.push({0, 0});

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
            if(cost[y][x]+arr[ny][nx] < cost[ny][nx]){
                cost[ny][nx] = cost[y][x]+arr[ny][nx];
                q.push({ny, nx});
            }
        }
    }
    return cost[N-1][N-1];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int num = 1;
    while(1){
        cin >> N;
        if(N == 0) break;
        input();
        cout << "Problem " << num++ << ": " << solution() << "\n";
    }
}