#include<iostream>
#define MAX 51
#define EMPTY 0
using namespace std;

struct DATA{int sum, cnt;};

int N, M, T;
int map[MAX][MAX];
int copy_map[MAX][MAX];
int dn[] = {-1, 1, 0, 0};
int dm[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M >> T;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) cin >> map[i][j];
    }
}

void rotate_clockwise(int x, int k){ // 시계 방향 회전
    for(int n=x; n<=N; n+=x){ // x의 배수 원판 회전
        for(int i=0; i<k; i++){
            int tmp = map[n][M];
            for(int m=M; m>1; m--) map[n][m] = map[n][m-1];
            map[n][1] = tmp;
        }
    }
}

void rotate_counterclockwise(int x, int k){ // 반시계 방향 회전
    for(int n=x; n<=N; n+=x){ // x의 배수 원판 회전
        for(int i=0; i<k; i++){
            int tmp = map[n][1];
            for(int m=1; m<M; m++) map[n][m] = map[n][m+1];
            map[n][M] = tmp;
        }
    }
}

DATA get_sum_cnt(){
    int sum=0, cnt=0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            if(map[i][j]==EMPTY) continue;
            sum+=map[i][j]; cnt++;
        }
    } return {sum, cnt};
}

void control_number(){

    for(int i=1; i<=N; i++){ // 동시에 확인하기 때문에!
        for(int j=1; j<=M; j++) copy_map[i][j] = map[i][j];
    }

    bool isEnd = false;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(map[i][j] == EMPTY) continue;
            
            int num = map[i][j];
            bool isRemove = false;
            for(int d=0; d<2; d++){ // 상 하 (범위 벗어나면 no)
                int nn = i+dn[d];
                int nm = j+dm[d];
                if(nn<1 || nn>N || nm<1 || nm>M) continue;
                if(map[nn][nm] == num){
                    isRemove = true;
                    copy_map[nn][nm] = EMPTY;
                }
            }
            for(int d=2; d<4; d++){ // 좌 우 (범위 벗어나면 modular)
                int nn = i+dn[d]; if(nn<1) nn+=N; if(nn>N) nn-=N;
                int nm = j+dm[d]; if(nm<1) nm+=M; if(nm>M) nm-=M;
                if(map[nn][nm] == num){
                    isRemove = true;
                    copy_map[nn][nm] = EMPTY;
                }
            }
            if(isRemove) {
                copy_map[i][j] = EMPTY;
                isEnd = true;
            }
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) map[i][j] = copy_map[i][j];
    }

    if(isEnd) return; // 인접하면서 같은 수를 모두 지운 경우

    DATA tmp = get_sum_cnt();
    int sum=tmp.sum, cnt=tmp.cnt;
    float mean = sum*1.0/cnt; // 원판에 적힌 수의 평균
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(map[i][j]==EMPTY) continue; // 빈칸
            if(map[i][j] < mean) map[i][j]++; // 평균 보다 작은 수
            else if(map[i][j] > mean) map[i][j]--; // 평균보다 큰 수 
        }
    }
}

void solution(){
    int x, d, k;
    while(T--){
        cin >> x >> d >> k;

        // 원판 회전
        if(d==0) rotate_clockwise(x, k);
        else rotate_counterclockwise(x, k);

        // 인접한 수 or 평균 처리
        control_number();
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    cout << get_sum_cnt().sum;
}