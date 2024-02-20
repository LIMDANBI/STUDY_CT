#include<iostream>
#include<vector>
#include<queue>
#define MAX 505
#define INF 1e9
using namespace std;

struct ROAD{int nxt, cost;};
struct PQ{
    int cur, cost;
    bool operator < (const PQ &pq) const {
        return cost > pq.cost;
    }
};

int N; // 장소의 수
int M; // 도로의 수
int S, D; // 시작점, 도착점
int dist[MAX]; // 최단 경로
bool visited[MAX]; // 방문 여부
vector<ROAD> road[MAX]; // 도로 정보
vector<ROAD> invRoad[MAX]; // 도로 정보 (역)

void init(){
    for (int i = 0; i < MAX; i++) {
        road[i].clear();
        invRoad[i].clear();
    }
}

void input(){
    cin >> N >> M;
    cin >> S >> D;

    int u, v, p;
    for (int i = 0; i < M; i++){
        cin >> u >> v >> p;
        road[u].push_back((ROAD){v, p});
        invRoad[v].push_back((ROAD){u, p});
    }
}

void dijkstra(){

    // 1. 초기화
    for (int i = 0; i < N; i++)
        dist[i] = INF;

    // 2. 시작점 처리
    priority_queue<PQ> pq;
    pq.push((PQ){S, 0});
    dist[S] = 0;

    // 3. 다익스트라
    while (!pq.empty()){
        int cur = pq.top().cur;
        pq.pop();

        for(auto n : road[cur]){
            int nxt = n.nxt;
            int ncost = dist[cur] + n.cost;
            if(ncost<dist[nxt]){
                pq.push((PQ){nxt, ncost});
                dist[nxt] = ncost;
            }
        }
    }
}

void remove_shortest(){

    // 1. 초기화
    for (int i = 0; i < N; i++)
        visited[i] = false;
    
    // 2. 시작점 처리
    queue<int> q;
    q.push(D);

    // 3. 최단 경로 제거
    while(!q.empty()){
        int cur = q.front(); q.pop();
        if(visited[cur]) continue;
        visited[cur] = true;

        for(auto n : invRoad[cur]){
            int nxt = n.nxt;
            int cost = n.cost;
            if(dist[nxt] + cost == dist[cur]){ // 최단 경로에 포함되는 경우
                q.push(nxt);
                for (int i=0; i<(int)road[nxt].size(); i++){
                    if(road[nxt][i].nxt == cur) road[nxt][i].cost = INF;
                }
            } 
        }
    }
}

void solve(){

    // 1. 최단 경로 찾기
    dijkstra();

    // 2. 최단 경로 제거
    remove_shortest();

    // 3. 거의 최단 경로 찾기
    dijkstra();

    if(dist[D]==INF) cout << "-1\n";
    else cout << dist[D] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("../test/input.txt", "r", stdin);
    while(true){
        init();
        input();
        if(N==0 && M==0) break; // 입력 종료 조건
        solve();
    }
}