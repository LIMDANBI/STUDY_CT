#include<iostream>
#include<cstring>
#include<queue>
#define MAX 100
#define INIT 3
using namespace std;

int R, C, K;
int cntArr[MAX+1];
int rnum=0, cnum=0;
int A[MAX][MAX], copyA[MAX][MAX];

struct DATA{
    int num, cnt;
    bool operator < (const DATA &d) const{
        if(cnt == d.cnt) return num > d.num; // 숫자 오름 차순 (2)
        else return cnt > d.cnt; // 등장 횟수 오름 차순 (1)
    }
};

void input(){
    cin >> R >> C >> K;
    for(int i=0; i<INIT; i++){
        for(int j=0; j<INIT; j++) cin >> A[i][j];
    } rnum = cnum = INIT;
}

void copy_and_init(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) {
            A[i][j] = copyA[i][j];
            copyA[i][j] = 0;
        }
    }   
}

void row_operation(){ // R 연산

    int max_cnum = cnum;
    for(int r=0; r<rnum; r++){

        priority_queue<DATA> pq;
        memset(cntArr, 0, sizeof(cntArr)); // init
        for(int c=0; c<cnum; c++) cntArr[A[r][c]]++; // 등장 빈도 count
        for(int num=1; num<=MAX; num++){ // 1 ≤ k ≤ 100
            if(cntArr[num] == 0) continue; // 0은 무시
            pq.push({num, cntArr[num]}); // 숫자, 빈도
        }

        max_cnum = max(max_cnum, min(2*(int)pq.size(), MAX)); // max 값 Update

        int c = 0, cnt, num;
        while(!pq.empty() && c<MAX){ // 정렬된 값 대입
            num = pq.top().num;
            cnt = pq.top().cnt; 
            pq.pop();
            copyA[r][c++] = num;
            copyA[r][c++] = cnt;
        }
    }

    cnum = max_cnum; // max 값 반영 (가장 큰 행을 기준으로 모든 행의 크기가 변함)
}

void col_operation(){ // C 연산
    int max_rnum = rnum;
    for(int c=0; c<cnum; c++){

        priority_queue<DATA> pq;
        memset(cntArr, 0, sizeof(cntArr)); // init
        for(int r=0; r<rnum; r++) cntArr[A[r][c]]++; // 등장 빈도 count
        for(int num=1; num<=MAX; num++){ // 1 ≤ k ≤ 100
            if(cntArr[num] == 0) continue; // 0은 무시
            pq.push({num, cntArr[num]}); // 숫자, 빈도
        }

        max_rnum = max(max_rnum, min(2*(int)pq.size(), MAX)); // max 값 Update

        int r = 0, cnt, num;
        while(!pq.empty() && r<MAX){ // 정렬된 값 대입
            num = pq.top().num;
            cnt = pq.top().cnt; 
            pq.pop();
            copyA[r++][c] = num;
            copyA[r++][c] = cnt;
        }
    }

    rnum = max_rnum; // max 값 반영 (가장 큰 열을 기준으로 모든 열의 크기가 변함)
}

void solution(){
    int ans = 0;
    while(ans++ <= 100){
        if(A[R-1][C-1] == K) {
            ans--;
            break;
        }
        if(rnum >= cnum) row_operation(); // R 연산
        else col_operation(); // C 연산
        copy_and_init();
    }
    if(ans > 100) cout << -1; // 100초가 지나도 A[r][c] = k가 되지 않으면 -1을 출력
    else cout << ans; // A[r][c]에 들어있는 값이 k가 되기 위한 연산의 최소 시간  
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}