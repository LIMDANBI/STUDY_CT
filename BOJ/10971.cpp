#include<iostream>
#include<cstring>
#define MAX 11
#define INF 1000000001
using namespace std;

int N, END;
int ans = INF;
int cost[MAX][MAX];
int dp[MAX][1<<MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> cost[i][j];
    }
}

int solution(int now, int visit){
    if(visit == END){ // 모두 방문하고
        if(cost[now][0]==0) return INF;
        return cost[now][0]; // 출발지로 돌아갈 수 있는 경우
    }

    int &res = dp[now][visit];
    if(res!=-1) return res; // 이미 값이 저장되어 있는 경우  
    res = INF;
    for(int next=0; next<N; next++){
        if(cost[now][next]==0 || (visit&(1<<next))!=0) continue; // 경로가 없거나, 이미 방문한 경우
        res = min(res, cost[now][next]+solution(next, visit|(1<<next)));
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    END = (1<<N)-1;
    memset(dp, -1, sizeof(dp));
    cout << solution(0, 1); // 외판원 순회에 필요한 최소 비용 출력 (출발지 : 0)
}