#include<iostream>
#include<vector>
#include<queue>
#define MAX 105
#define INF 1e9
using namespace std;

struct ROAD{int nxt, cost;};
struct PQ{
    int cur, cost;
    bool operator < (const PQ &p) const{
        return cost > p.cost;
    }
};

int N, M; // 공장 수, 도로 정보 수
int dist[MAX];
vector<ROAD> road[MAX];

void input(){
    cin >> N >> M;

    int a, b, c;
    for (int i = 0; i < M; i++){
        cin >> a >> b >> c;
        road[a].push_back({b, c});
        road[b].push_back({a, c});
    }
}

void init(){
    for (int i = 1; i <= N; i++)
        dist[i] = INF;
}

int dijkstra(int start){

    // 1. 초기화
    priority_queue<PQ> pq;
    pq.push({start, 0});
    dist[start] = 0;

    // 2. 다익스트라
    while (!pq.empty()){
        int cur = pq.top().cur;
        pq.pop();

        for(auto r : road[cur]){
            int nxt = r.nxt;
            int cost = r.cost;

            if(dist[cur]+cost < dist[nxt]){
                dist[nxt] = dist[cur] + cost;
                pq.push({nxt, dist[cur] + cost});
            }
        }
    }

    // 3. 가장 먼 공장의 거리 구하기
    int res = 0;
    for (int i = 1; i <= N; i++)
        res = max(res, dist[i]);
    return res;
}

void solve(){

    int ans = INF;

    // 각 위치에 공장을 세워 봄
    for (int start = 1; start <= N; start++){
        
        // 1. 초기화
        init();

        // 2. 다익스트라
        ans = min(ans, dijkstra(start));
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}