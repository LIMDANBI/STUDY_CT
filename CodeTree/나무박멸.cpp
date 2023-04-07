#include<iostream>
#include<queue>
#define MAX 21
#define EMPTY 0
#define WALL -1
using namespace std;

struct POS{
    int y, x, cnt;
    bool operator < (const POS &p) const{
        if(cnt == p.cnt){
            if(y == p.y) return x > p.x; // 행이 작은 순
            return y > p.y; // 행이 같은 경우에는 열이 작은 칸에
        }
        return cnt < p.cnt;
    }
};

int N, M, K, C;
int jechoje[MAX][MAX];
int map[MAX][MAX], tmpMap[MAX][MAX];
int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};

void input(){
    cin >> N >> M >> K >> C;
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++)
            cin >> map[y][x];
    }
}

void grow(){ // 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            if(map[y][x]==WALL || map[y][x]==EMPTY) continue; // 나무가 아닌 경우 ,,

            int cnt = 0;
            for (int d = 1; d < 8; d += 2){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue; // 범위를 벗어나는 경우
                if(map[ny][nx]==WALL || map[ny][nx]==EMPTY) continue; // 나무가 아닌 경우
                map[y][x]++; // 동시에 일어나지만, 새로 생기는 것은 아니기 때문에 상관 없음
            }
        }
    }
}

void breeding(){
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            if(map[y][x]==WALL || map[y][x]==EMPTY) continue; // 나무가 아닌 경우 ,,
            
            int cnt = 0; // 총 번식이 가능한 칸의 개수
            int num = map[y][x]; // 칸의 나무 그루 수
            for (int d = 1; d < 8; d += 2){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue; // 범위를 벗어나는 경우
                if(map[ny][nx]==EMPTY && !jechoje[ny][nx]) cnt++; // 빈칸이 아니거나, 제초제가 있는 경우
            }

            if(cnt == 0) continue; // division zeor 방지
            num /= cnt;
            for (int d = 1; d < 8; d += 2){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if(ny<0 || ny>=N || nx<0 || nx>=N) continue; // 범위를 벗어나는 경우
                if(map[ny][nx]!=EMPTY || jechoje[ny][nx]) continue; // 빈칸이 아니거나, 제초제가 있는 경우
                tmpMap[ny][nx] += num; // 번식
            }
        }
    }

    for (int y = 0; y < N; y++){ // 번식 과정은 모든 나무에서 동시에 일어남
        for (int x = 0; x < N; x++){
            map[y][x] += tmpMap[y][x];
            tmpMap[y][x] = 0;
        }
    }
}

POS get_spread_pos(){
    priority_queue<POS> pq; 
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++){
            if(map[y][x] == WALL) continue;
            if(map[y][x]==EMPTY) { // 벽, 빈칸
                pq.push({y, x, 0});
                continue;
            }
            // 나무가 있는 칸
            int cnt = map[y][x];
            for (int d = 0; d < 8; d+=2){
                for (int k = 1; k <= K; k++){
                    int ny = y + dy[d] * k;
                    int nx = x + dx[d] * k;
                    if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
                    if(map[ny][nx]==EMPTY || map[ny][nx]==WALL) break;
                    cnt += map[ny][nx];
                }
            }
            pq.push({y, x, cnt});
        }
    }
    return pq.top();
}

void spread(int y, int x){ // 제초제 뿌림

    // 가운데 지점도 처리!! 
    jechoje[y][x] = C+1; 
    if(map[y][x]==WALL || map[y][x]==EMPTY) return;
    if(map[y][x] != WALL) map[y][x] = EMPTY;

    for (int d = 0; d < 8; d += 2){
        for (int k = 1; k <= K; k++){
            int ny = y + dy[d] * k;
            int nx = x + dx[d] * k;
            if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
            jechoje[ny][nx] = C+1;
            if(map[ny][nx]==WALL || map[ny][nx]==EMPTY) break; // 해당 칸 까지는 제초제가 뿌려짐
            map[ny][nx] = EMPTY;
        }
    }
}

void reduce_jechohe(){
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            if(jechoje[y][x])
                jechoje[y][x]--;
        }
    }
}

void solution(){  // m년 동안 총 박멸한 나무의 그루 수
    int ans = 0;
    while (M--){
        grow();
        breeding();
        POS p =  get_spread_pos();
        ans += p.cnt;
        spread(p.y, p.x);
        reduce_jechohe();
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}