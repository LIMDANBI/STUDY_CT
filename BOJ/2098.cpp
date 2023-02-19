#include<iostream>
#define MAX 16
#define INF 1000000001
using namespace std;

int N, END;
int cost[MAX][MAX];
int dp[MAX][1<<MAX];

void input(){
    cin >> N;
    END = (1<<N)-1;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> cost[i][j];
    }
}

int solution(int now, int visit){ // 외판원의 순회에 필요한 최소 비용
    if(visit == END){ // 모두 방문한 경우
        if(cost[now][0]==0) return INF; 
        return cost[now][0]; // 출발지로 돌아갈 수 있다면
    }

    int &res = dp[now][visit]; // 이미 값을 저장해둔 경우
    if(res!=0) return res; res = INF;
    for(int next=0; next<N; next++){
        if(cost[now][next]==0 || visit&(1<<next)) continue; // 경로가 없거나, 이미 방문한 경우
        res = min(res, cost[now][next]+solution(next, visit|(1<<next)));
    }
    return res;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solution(0, 1); // 0번 출발지에서 시작 (어디서 시작하든 결과는 같음)
}