#include <iostream>
#include <queue>
#define MAX 21
#define EMPTY 0
#define WALL -1
#define pii pair<int, int>
using namespace std;

struct POSITION{
    int cnt, y, x;
    bool operator < (const POSITION &p) const {
        if(cnt == p.cnt){
            if(y == p.y) return x > p.x;
            return y > p.y;
        } return cnt < p.cnt;
    }
};

int N, M, K, C, ans;
int map[MAX][MAX];
int tmp_map[MAX][MAX];
int herbicide[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};
int dhy[] = {-1, -1, 1, 1};
int dhx[] = {-1, 1, -1, 1};

void input(){
    cin >> N >> M >> K >> C;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++) cin >> map[y][x];
    }
}

void grow_tree(){
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            if(map[y][x]==EMPTY || map[y][x]==WALL) continue;
            
            int cnt = 0; // 인접한 나무가 있는 칸 수
            for(int d=0; d<4; d++){
                int ny = y+dy[d];
                int nx = x+dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
                if(map[ny][nx] > 0) cnt++;
            }
            map[y][x] += cnt;
        }
    }
}

void breed_tree(){
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            if(map[y][x] <= 0) continue; // 나무가 없는 칸

            int ny, nx, cnt = 0;
            for(int d=0; d<4; d++){
                ny = y+dy[d]; nx = x+dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
                if(herbicide[ny][nx] == EMPTY && map[ny][nx] == EMPTY) cnt++;
            }
            if(cnt == 0) continue; // 번식 가능한 칸이 없는 경우
            for(int d=0; d<4; d++){
                ny = y+dy[d]; nx = x+dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
                if(herbicide[ny][nx] == EMPTY && map[ny][nx] == EMPTY) tmp_map[ny][nx] += map[y][x]/cnt;
            }
        }
    }
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            map[y][x] += tmp_map[y][x];
            tmp_map[y][x] = 0; // init
        }
    }
}

pii find_position(){
    priority_queue<POSITION> pq;

    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            if(map[y][x] == EMPTY) pq.push({0, y, x}); // 나무가 없는 칸
            else if(map[y][x] != WALL){ // 나무가 있는 칸
                
                int cnt = map[y][x];
                for(int d=0; d<4; d++){
                    for(int k=1; k<=K; k++){
                        int ny = y + dhy[d]*k;
                        int nx = x + dhx[d]*k;
                        if(ny<0 || ny>=N || nx<0 || nx>=N || map[ny][nx]<=0) break;
                        cnt += map[ny][nx];
                    }
                }
                pq.push({cnt, y, x});
            }   
        }
    }
    ans += pq.top().cnt;
    return {pq.top().y, pq.top().x};
}

void spray_herbicide(){
    pii pos = find_position();
    int y = pos.first;
    int x = pos.second;

    // 주의
    map[y][x] = EMPTY;
    herbicide[y][x] = C+1;

    for(int d=0; d<4; d++){
        for(int k=1; k<=K; k++){
            int ny = y + dhy[d]*k;
            int nx = x + dhx[d]*k;
            if(ny<0 || ny>=N || nx<0 || nx>=N) break;
            herbicide[ny][nx] = C+1;
            bool isend = false;
            if(map[ny][nx]==EMPTY || map[ny][nx]==WALL) isend = true;
            if(map[ny][nx] > 0) map[ny][nx] = EMPTY;
            if(isend) break; // 해당 칸 까지는 뿌려짐
        }
    }
}

void decrease_herbicide(){
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++) {
            if(herbicide[y][x]) herbicide[y][x]--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    while(M--){
        grow_tree();
        breed_tree();
        spray_herbicide();
        // print_map(); exit(0);
        decrease_herbicide();
    }
    cout << ans; // m년 동안 총 박멸한 나무의 그루 수
    return 0;
}