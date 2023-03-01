#include<iostream>
#include<queue>
#define MAX 50
#define EMPTY 0
using namespace std;

int N, M;
int sy, sx;
int map[MAX][MAX];
int dy[] = {0, -1, 1, 0, 0}; // ↑, ↓, ←, → (1, 2, 3, 4)
int dx[] = {0, 0, 0, -1, 1};
int my[] = {0, 1, 0, -1}; // 좌, 하, 우, 상
int mx[] = {-1, 0, 1, 0};

void input(){
    cin >> N >> M;
    sy = sx = (N+1)/2; // 상어의 위치
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++) cin >> map[i][j];
    }
}

void blizard(int d, int s){
    int y=sy, x=sx;
    for(int i=0; i<s; i++){ // s ≤ (N-1)/2
        y+=dy[d]; x+=dx[d];
        map[y][x] = EMPTY; // 구슬 파괴 (by 얼음 파편)
    }
}

void move_marble(){
    queue<int> q;

    int y=sy, x=sx, cnt=0; // 초기 위치, 이동 범위
    for(int d=0; x!=0; d++){ d%=4;
        if(d%2==0) cnt++;
        for(int i=0; i<cnt; i++){
            y+=my[d]; x+=mx[d];
            if(map[y][x]) { // 구슬이 있는 경우
                q.push(map[y][x]); 
                map[y][x]=EMPTY;
            }
        }
    }

    y=sy; x=sx; cnt=0; // init
    for(int d=0; x!=0; d++){ d%=4;
        if(d%2==0) cnt++;
        for(int i=0; i<cnt; i++){
            y+=my[d]; x+=mx[d];
            if(q.empty()) {x=0; break;}
            else {map[y][x] = q.front(); q.pop();}
        }
    }
}

int bomb_marble(){ //  1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수) 반환

    int res = 0;
    while(1){ // 더이상 폭발하는 구슬이 없을때까지 반복
    
        bool isEnd = true; // 4개 이상 연속 구슬이 없는지
        int y=sy, x=sx, cnt=0; // 초기 위치, 이동 범위
        
        int before=0; // 이전 구슬 번호
        vector<pair<int, int> > pos;
        for(int d=0; x!=0; d++){ d%=4;
            if(d%2==0) cnt++;
            for(int i=0; i<cnt; i++){
                y+=my[d]; x+=mx[d];
                if(map[y][x]==before) pos.push_back(make_pair(y,x)); // 이전 구슬과 같은 경우
                else{ // 이전 구슬과 다른 경우
                    if(pos.size() < 4){
                        pos.clear();
                        before = map[y][x]; // 구슬 번호 update
                        pos.push_back(make_pair(y,x)); // 새로운 구슬
                    }
                    else{
                        isEnd = false; // 구슬이 움직인 후 다시 확인 필요
                        res+=before * (int)pos.size(); // 구슬번호 * 개수
                        for(int i=0; i<(int)pos.size(); i++) map[pos[i].first][pos[i].second] = EMPTY; // 구슬 폭발
                        pos.clear(); // init
                        before = map[y][x]; // 구슬 번호 update
                        pos.push_back(make_pair(y,x));
                    }
                }
            }
        }
        if(isEnd) return res;
        else move_marble(); // 구슬 이동
    }
}

void change_marble(){
    queue<int> q;
    
    int y=sy, x=sx, cnt=0; // 초기 위치, 이동 범위
    int A=0, B=0; // 현재 구슬 개수, 번호
    for(int d=0; x!=0; d++){ d%=4;
        if(d%2==0) cnt++;
        for(int i=0; i<cnt; i++){
            y+=my[d]; x+=mx[d];
            if(map[y][x]==B) A++; // 이전 구슬 번호와 같은 경우, 개수 증가
            else{
                if(B!=0) {q.push(A); q.push(B);}
                B = map[y][x]; // 새 구슬 번호
                A = 1; // init
            }
        }
    }

    y=sy; x=sx; cnt=0; // init
    for(int d=0; x!=0; d++){ d%=4;
        if(d%2==0) cnt++;
        for(int i=0; i<cnt; i++){
            y+=my[d]; x+=mx[d]; if(x==0) break; // 이 부분을 안넣어주면 75% 틀림 ^^
            if(q.empty()) map[y][x] = EMPTY; // 기존 구슬 칸 -> EMPTY!!
            else {map[y][x] = q.front(); q.pop();}
        }
    }
}

void solution(){ // 1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수) 출력
    int ans = 0;
    int d, s; // 마법의 방향, 거리 
    while(M--){
        cin >> d >> s;
        blizard(d, s); // 블리자드 마법 시전
        move_marble(); // 구슬 이동
        ans += bomb_marble(); // 구슬 폭발
        change_marble(); // 구슬 변화
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}