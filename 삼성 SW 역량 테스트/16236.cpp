#include<iostream>
#include<cstring>
#include<queue>
#define MAX 21
using namespace std;

struct SHARK{
    int y, x, size, eat; // 위치, 크기, 먹은 물고기 수 
} shark;

struct PRIORITY{
    int dist, y, x;
    bool operator < (const PRIORITY &p) const { // operator 재정의
        if(dist == p.dist){
            if(y == p.y) return x > p.x; // 가장 왼쪽에 있는 물고기
            return y > p.y; // 가장 위에 있는 물고기
        } return dist > p.dist; // 거리가 가까운 물고기
    }
};

int N, ans=0;
int arr[MAX][MAX];
int dy[] = {-1, 1, 0, 0}; // 상하좌우
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 9){ // 아기 상어의 위치
                shark = {i, j, 2, 0};
                arr[i][j] = 0;
            }
        }
    }
}

void solution(){

    bool visited[MAX][MAX];
    
    while(1){
        priority_queue<PRIORITY> pq; // 먹을 수 있는 물고기들 (우선 순위로)
        memset(visited, false, sizeof(visited));

        queue<PRIORITY> q;
        q.push({0, shark.y, shark.x});
        visited[shark.y][shark.x] = true;

        while (!q.empty()){
            int y = q.front().y;
            int x = q.front().x;
            int dist = q.front().dist;
            q.pop();

            for(int d=0; d<4; d++){
                int ny = y+dy[d];
                int nx = x+dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어나는 경우, 이미 방문한 경우
                if(arr[ny][nx] > shark.size) continue; // 큰 경우, 지나칠 수 없음
                visited[ny][nx] = true; // 중복 방문 방지
                q.push({dist+1, ny, nx}); // 작거나 같은 경우, 지나칠 수 있음
                if(arr[ny][nx] < shark.size && arr[ny][nx]!=0) pq.push({dist+1, ny, nx}); // 작은 경우(빈 공간 x), 먹을 수 있음
            }
        }
        
        if(pq.size() == 0) return; // 더 이상 먹을 수 있는 물고기가 없는 경우 

        arr[pq.top().y][pq.top().x] = 0; // 물고기를 먹음
        ans += pq.top().dist; // 거리 count
        
        // 상어 정보 update
        shark.y = pq.top().y;
        shark.x = pq.top().x;
        shark.eat++;
        if(shark.eat == shark.size){ // 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가
            shark.size++;
            shark.eat = 0;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    cout << ans;
}