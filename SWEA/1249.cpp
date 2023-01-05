#include<iostream>
#include<cstring>
#include<queue>
#define MAX 101
#define INF 100000001
using namespace std;

int N;
int arr[MAX][MAX];
int cost[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    
    string line;
    for(int i=0; i<N; i++){
         cin >> line;
        for(int j=0; j<N; j++) {
            arr[i][j] = line[j] - '0';
            cost[i][j] = INF; // init
        }
    }
}

int solution(){

    queue<pair<int, int>> q;
    cost[0][0] = 0;
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
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}