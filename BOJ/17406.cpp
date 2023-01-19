#include<iostream>
#include<vector>
#define MAX 51
#define MAX_K 7
#define INF 1000000001
using namespace std;

struct OPER{int r, c, s;};
vector<OPER> v;

int N, M, K;
int ans = INF;
int arr[MAX][MAX];
bool visited[MAX_K];

void print_arr(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) cout << arr[i][j] << " ";
        cout << "\n";
    }
}

void input(){
    cin >> N >> M >> K;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) cin >> arr[i][j];
    }

    int r, c, s;
    for(int i=0; i<K; i++){
        cin >> r >> c >> s;
        v.push_back({r-1, c-1, s}); // start with 0
    }
}

void rotate_arr(int r, int c, int s){

    int ur = r-s, uc = c-s; // 좌측 상단 좌표
    int dr = r+s, dc = c+s; // 우측 하단 좌표

    while(1){
        if(ur >= dr) break; // 종료 조건
        int tmp = arr[ur][uc];
        for(int i=ur; i<dr; i++) arr[i][uc] = arr[i+1][uc]; // 좌
        for(int j=uc; j<dc; j++) arr[dr][j] = arr[dr][j+1]; // 하
        for(int i=dr; i>ur; i--) arr[i][dc] = arr[i-1][dc]; // 우
        for(int j=dc; j>uc; j--) arr[ur][j] = arr[ur][j-1]; // 상
        arr[ur][uc+1] = tmp;
        ur++; uc++;
        dr--; dc--;
    }
}

int get_min_val(){
    int res = INF;
    for(int i=0; i<N; i++){
        int sum = 0;
        for(int j=0; j<M; j++) sum+=arr[i][j];
        res = min(res, sum);
    }
    return res;
}

void solution(int cnt){

    if(cnt == K){
        ans = min(ans, get_min_val());
        return;
    }

    for(int i=0; i<K; i++){

        if(visited[i]) continue; // 이미 사용한 경우
        visited[i] = true; // 사용

        // save state
        int copy_arr[MAX][MAX];
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++) copy_arr[i][j] = arr[i][j];
        }
        
        rotate_arr(v[i].r, v[i].c, v[i].s); // 회전 연산
        solution(cnt+1); // 순열 구현
        
        visited[i] = false; // 다른 순열에서 사용하기 위해

        // recovery
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++) arr[i][j] = copy_arr[i][j];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(0);
    cout << ans;
}