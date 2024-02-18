#include<iostream>
#include<vector>
#include<queue>
#define MAX 1005
using namespace std;

int N; // 건물의 개수
int K; // 건물간의 건설순서 규칙의 총 개수
int W; // 백준이가 승리하기 위해 건설해야 할 건물의 번호
int D[MAX]; // 각 건물당 건설에 걸리는 시간
int cost[MAX]; // 순서에 따른 건물 건설에 걸리는 시간
int indegree[MAX]; // 다른 노드로부터 들어오는 간선의 개수
vector<int> v[MAX]; // 건설 순서

void init(){
    for(int i=1; i<MAX; i++){
        cost[i] = 0;
        indegree[i] = 0;
        v[i].clear();
    }
}

void input(){
    cin >> N >> K;
    for(int i=1; i<=N; i++) cin >> D[i];

    int X, Y;
    for(int i=0; i<K; i++){
        cin >> X >> Y;
        indegree[Y]++;
        v[X].push_back(Y);
    }
    cin >> W;
}

void solve(){

    // 1. 시작점 (진입 차수가 0) queue에 넣기
    queue<int> q;
    for(int n=1; n<=N; n++){
        if(indegree[n] == 0) {
            q.push(n);
            cost[n] = D[n];
        }
    }

    // 2. 건물 건설
    while (!q.empty()){

        int cur = q.front();
        q.pop();

        if(cur == W){
            cout << cost[W] << "\n";
            return;
        }

        for(int nxt : v[cur]){
            if(--indegree[nxt] == 0){
                cost[nxt] = max(cost[cur], cost[nxt]) + D[nxt];
                q.push(nxt);
            }
            else{
                cost[nxt] = max(cost[nxt], cost[cur]);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        init();
        input();
        solve();
    }
}