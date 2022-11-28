#include<iostream>
#include<vector>
#include<queue>
#define MAX 1001
#define INF 987654321
using namespace std;

int N, M, X;
int dist[MAX], sum_dist[MAX];
vector<pair<int, int>> path[MAX], inverse_path[MAX];

void input(){
    cin >> N >> M >> X;

    int a, b, t;
    for(int i=0; i<M; i++){
        cin >> a >> b >> t;
        path[a].push_back({b, t}); // 돌아오는 길 (X - > 다른 마을)
        inverse_path[b].push_back({a, t}); // 가는 길 (다른 마을 -> X)
    }
}

void dijkstra(vector<pair<int, int>> *v){
    for(int i=1; i<=N; i++) dist[i] = INF; // init
    priority_queue<pair<int, int>> pq;
    pq.push({0, X}); // start point : X
    dist[X] = 0;

    while(!pq.empty()){
        int now_node = pq.top().second;
        int now_cost = -pq.top().first;
        pq.pop();

        for(int i=0; i<v[now_node].size(); i++){
            int next_node = v[now_node][i].first;
            int new_cost = dist[now_node]+v[now_node][i].second;
            if(new_cost > dist[next_node]) continue;
            dist[next_node] = new_cost;
            pq.push({-new_cost, next_node});
        }
    }

    for(int i=1; i<=N; i++) sum_dist[i]+=dist[i];
}

void solution(){ 
    dijkstra(path);
    dijkstra(inverse_path);

    int ans = 0;
    for(int i=1; i<=N; i++) ans = max(ans, sum_dist[i]);
    cout << ans << "\n"; // N명의 학생들 중 오고 가는데 가장 오래 걸리는 학생의 소요시간
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}