#include<iostream>
#define MAX 15
#define INF 1e9
using namespace std;

int N;
int minCost = INF;
bool visited[MAX];
int cost[MAX][MAX];
int sol[MAX], seq[MAX];

void input(){
    cin >> N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++) cin >> cost[i][j];
    }
}

void dfs(int n){ // 완전탐색 (순열)
    if(n >= N){
        int tmp = 0;

        // 해당 순서 총 비용 계산
        for(int idx=0; idx<N; idx++) tmp += cost[idx][seq[idx]];
        
        // 더 적은 비용이 드는 경우
        if(tmp < minCost){
            minCost = tmp;
            for(int i=0; i<N; i++) sol[i] = seq[i];
        }
        return ;
    }

    for(int idx=0; idx<N; idx++){
        if(visited[idx]) continue;
        visited[idx] = true;
        seq[n] = idx; 
        dfs(n+1);
        visited[idx] = false;
    }
}

void output(){
    cout << minCost << "\n";
    for(int i=0; i<N; i++) cout << sol[i]+1 << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(0);
    output();
}