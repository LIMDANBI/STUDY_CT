#include<iostream>
#include<cstring>
#include<queue>
#define MAX 51
using namespace std;

struct DATA{
    int y, x, cnt;
    bool operator < (const DATA &d) const{
        return cnt > d.cnt;
    }
};


int N;
bool map[MAX][MAX];
bool visited[MAX][MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N ;
    for (int i = 0; i < N; i++){
        string line; cin >> line;
        for (int j = 0; j < N; j++){
            map[i][j] = line[j] - '0';
        }
    }
}

void solution(){
    priority_queue<DATA> pq;
    visited[0][0][0] = true;
    pq.push({0, 0, 0});

    while(!pq.empty()){
        int y = pq.top().y;
        int x = pq.top().x;
        int cnt = pq.top().cnt;
        pq.pop();

        if(y==N-1 && x==N-1){
            cout << cnt;
            return;
        }

        for (int d = 0; d < 4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx][cnt]) continue;
            visited[ny][nx][cnt] = true;
            if(map[ny][nx]) pq.push({ny, nx, cnt});
            else pq.push({ny, nx, cnt+1});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}