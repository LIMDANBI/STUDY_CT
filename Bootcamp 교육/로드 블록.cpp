#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#define MAX 105
#define INF 1e9
using namespace std;

struct DATA{int nxt, cost;};
struct PATH{int a, b;};
struct PQ{
    int cur, cost;
    bool operator < (PQ const &tmp) const{
        return cost > tmp.cost; // min heap
    }
};

int N, M;
int ta, tb;
int prv[MAX];
int dist[MAX];
vector<DATA> v[MAX];

void input(){
    cin >> N >> M;
    
    int a, b, c;
    for(int i=0; i<M; i++){ // 경로 정보 저장
        cin >> a >> b >> c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }
}

int dijkstra(int start, int dest){

    // 1. 초기화
    for(int i=1; i<=N; i++) dist[i] = INF;
    
    // 2. 시작점 처리
    priority_queue<PQ> pq;
    pq.push({start, 0});
    dist[start] = 0;

    // 3. 다익스트라
    while (!pq.empty()){
        int cur = pq.top().cur;
        int cost = pq.top().cost;
        pq.pop();

        for(auto e : v[cur]){
            int pcost = dist[e.nxt];
            int ncost = cost + e.cost;
            if(ncost < pcost){
                pq.push({e.nxt, ncost});
                dist[e.nxt] = ncost;
                prv[e.nxt] = cur; // 경로 저장
            }
        }

    }
    return dist[dest];
}

void twice(int a, int b){
    for(int i=0; i<(int)v[a].size(); i++){
        if(v[a][i].nxt == b) v[a][i].cost*=2;
    }
    for(int i=0; i<(int)v[b].size(); i++){
        if(v[b][i].nxt == a) v[b][i].cost*=2;
    }
}

void recovery(int a, int b){
    for(int i=0; i<(int)v[a].size(); i++){
        if(v[a][i].nxt == b) v[a][i].cost/=2;
    }
    for(int i=0; i<(int)v[b].size(); i++){
        if(v[b][i].nxt == a) v[b][i].cost/=2;
    }
}

void solve(){
    
    // 1. 기존 최단 경로
    int dist1 = dijkstra(1, N);
    int dist2 = 0;

    // 2. 최단 경로 찾기
    int cur = N;
    deque<PATH> paths;
    while(prv[cur]){
        paths.push_front({prv[cur], cur});
        cur = prv[cur];
    }

    // 2. 최단 경로 내 경로의 길이를 2배 늘리고, 다익스트라 (최대 99개)
    for(auto p : paths){

        // 1) 2배 늘림
        twice(p.a, p.b);
        
        // 2) 다익스트라
        dist2 = max(dist2, dijkstra(1, N));        
        
        // 3) 복원
        recovery(p.a, p.b);
    }

    // 3. 정답 출력
    cout << dist2-dist1;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}