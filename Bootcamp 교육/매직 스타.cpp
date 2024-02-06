#include<iostream>
#include<vector>
#define R 5
#define C 9
#define MAX 13
#define SUM 26
using namespace std;

struct POS{int y, x;};
vector<POS> pos;

int N;
int psum;
bool ismake;
int sum[MAX];
char map[R][C];
bool used[MAX];

void input(){
	for (int h=0; h<R; h++){
        for(int w=0; w<C; w++){
            cin >> map[h][w];
            if(map[h][w] == 'x'){
                pos.push_back({h, w});
            }
            else if(map[h][w] != '.'){
                used[map[h][w]-'A'+1] = true;
            }
        }
	}
}

void line_sum(int idx, char c){
    if(c=='.' || c=='x') return;
    sum[idx] += (c-'A'+1);
}

void init(){

    // 최대 depth
    N = (int) pos.size();

    // 2. 기존 line 합
    for(int y=1, x=0; x<C; x++) line_sum(0, map[y][x]);
    for(int y=3, x=0; x<C; x++) line_sum(1, map[y][x]);
    for(int y=0, x=4, cnt=0; cnt<4; cnt++) line_sum(2, map[y+cnt][x-cnt]);
    for(int y=0, x=4, cnt=0; cnt<4; cnt++) line_sum(3, map[y+cnt][x+cnt]);
    for(int y=4, x=4, cnt=0; cnt<4; cnt++) line_sum(4, map[y-cnt][x-cnt]);
    for(int y=4, x=4, cnt=0; cnt<4; cnt++) line_sum(5, map[y-cnt][x+cnt]);

    // 3. 1~12까지의 합
    for(int n=1; n<=12; n++) psum+=n;
}

void control_line_sum(int y, int x, int num){
    if(y == 1) sum[0] += num;
    if(y == 3) sum[1] += num;
    if(y+x == 4) sum[2] += num;
    if(x-y == 4) sum[3] += num;
    if(y-x == 0) sum[4] += num;
    if(x+y == 8) sum[5] += num;
}

void simul(int n, int r){

    // 1. 가지치기
    for(int i=0; i<6; i++){

        // 남은 수들을 다 합쳐도 라인의 합이 26이 안되는 경우
        if(sum[i]+r < SUM) return;

        // 라인의 합이 26이 넘은 경우
        if(sum[i] > SUM) return;
    }

    // 2. 이미 매직스타를 만든 경우
    if(ismake) return;

    // 3. 매직 스타를 만드는 데 성공한 경우
    if(N <= n){
        ismake = true;
        return;
    }

    // 4. 매직 스타를 만들어 봄
    int y = pos[n].y;
    int x = pos[n].x;
    for(int num=1; num<MAX&&!ismake; num++){ // 사전 순
        if(used[num]) continue;
        
        used[num] = true;
        map[y][x] = num + 'A' - 1;
        control_line_sum(y, x, num); // +
        
        simul(n+1, r-num); // 다음 선택

        used[num] = false;
        control_line_sum(y, x, -num); // -
    }
}

void solve(){
    
    // 1. 초기화
    init();

    // 2. 시뮬레이션
    simul(0, psum);
}

void output(){
	for (int h=0; h<R; h++){
        for(int w=0; w<C; w++)
            cout << map[h][w];
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}