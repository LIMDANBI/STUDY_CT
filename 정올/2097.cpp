#include<iostream>
#include<vector>
#include<queue>
#define MAX 105
#define INF 1000000001
#define pii pair<int, int>
using namespace std;

int N, M;
int cost[MAX]; // cost[k]: 1번역에서 k 역까지 가는데 걸리는 시간
int stopover[MAX]; // 경유지 저장
vector<pii> v[MAX];

void input(){
    cin >> N >> M;

    int c;
    for (int a = 1; a <= N; a++){
        for (int b = 1; b <= N; b++){
            cin >> c;
            v[a].push_back({c, b});
        }
        cost[a] = INF;
    }
}

void solve(){ // 목적 역까지 가는데 걸리는 최소 시간과 최소시간으로 가는 최단경로를 출력
    priority_queue<pii> pq; // cost, now
    pq.push({0, 1}); // 1번에서 출발
    cost[1] = 0;

    while (!pq.empty()){
        int c = pq.top().first;
        int a = pq.top().second;
        pq.pop();

        for (pii p : v[a]){
            int b = p.second;
            int nc = -c + p.first;
            if(nc < cost[b]){
                cost[b] = nc;
                stopover[b] = a; // a -> b
                pq.push({-nc, b});
            }
        }
    }
}

void output(){
    vector<int> path;
    path.push_back(M);
    int tmp = M;
    while(stopover[tmp]){
        path.push_back(stopover[tmp]);
        tmp = stopover[tmp];
    }

    cout << cost[M] << "\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}