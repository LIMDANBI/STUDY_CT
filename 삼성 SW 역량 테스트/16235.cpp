#include<iostream>
#include<deque>
#define MAX 11
using namespace std;

int N, M, K;
deque<int> tree[MAX][MAX];
int A[MAX][MAX], nutrient[MAX][MAX];
int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void input(){
    cin >> N >> M >> K;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++) {
            cin >> A[r][c];
            nutrient[r][c] = 5; // 가장 처음에 양분은 모든 칸에 5만큼 들어있음
        }
    }

    int r, c, age;
    for(int i=0; i<M; i++){ // 입력으로 주어지는 나무의 위치는 모두 서로 다름
        cin >> r >> c >> age;
        tree[r][c].push_back(age);
    }
}

void year(){

    // 봄 & 여름
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            int t; // 나무
            for(t=0; t<tree[r][c].size(); t++){
                if(tree[r][c][t] <= nutrient[r][c]) {
                    nutrient[r][c]-=tree[r][c][t]; // 자신의 나이만큼 양분을 먹고
                    tree[r][c][t]++; //  나이가 1 증가
                } else break;
            }
            for(int i=tree[r][c].size()-1; i>=t; i--){ // 양분을 먹지 못하고 즉시 죽은 나무
                nutrient[r][c]+=tree[r][c][i]/2; // 여름에 양분으로 변함
                tree[r][c].pop_back(); // 죽음
            }
        }
    }

    // 가을 - 나무 번식
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            for(int t=0; t<tree[r][c].size(); t++){
                if(tree[r][c][t]%5 == 0){ // 나이가 5의 배수
                    for(int d=0; d<8; d++){ // 나무 번식
                        int nr = r+dr[d];
                        int nc = c+dc[d];
                        if(nr<1 || nr>N || nc<1 || nc>N) continue;
                        tree[nr][nc].push_front(1); // 나이가 1인 나무가 생김 
                    }
                }
            }
        }
    }

    // 겨울 - 양분 추가
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++) nutrient[r][c]+=A[r][c];
    }
}

void output(){ // K년이 지난 후 살아남은 나무의 수
    int ans = 0;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++) ans+=tree[r][c].size();
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    while(K--) year();
    output();
}