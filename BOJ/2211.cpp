#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#define MAX 1005
#define INF 1e9
using namespace std;

struct COMPUTER { int nxt, cost; };
struct DIJKSTRA { 
    int cur, cost; 
    bool operator < (const DIJKSTRA &d) const{
        return cost > d.cost;
    }
};
struct CONNECT { 
    int a, b; 
    bool operator < (const CONNECT &c) const{
        if (a != c.a) return a < c.a;
        return b < c.b;
    }
};

int N, M;
int prv[MAX];
int dist[MAX];
vector<COMPUTER> computer[MAX];

void input(){
    cin >> N >> M;

    int a, b, c;
    for (int i = 0; i < M; i++){
        cin >> a >> b >> c;
        computer[a].push_back((COMPUTER){b, c});
        computer[b].push_back((COMPUTER){a, c});
    }
}

void solve(){

    // 1. 초기화
    for (int i = 1; i <= N; i++)
        dist[i] = INF;
    
    priority_queue<DIJKSTRA> pq;
    pq.push((DIJKSTRA){1, 0});
    dist[1] = 0;

    // 2. 다익스트라
    while (!pq.empty()){
        int cur = pq.top().cur;
        int cost = pq.top().cost;
        pq.pop();

        for(auto c : computer[cur]){
            int nnode = c.nxt;
            int ncost = cost + c.cost;

            if(ncost < dist[nnode]){
                pq.push((DIJKSTRA){nnode, ncost});
                dist[nnode] = ncost;
                prv[nnode] = cur;
            }
        }
    }

    // 3. 복구할 회선 구하기
    set<CONNECT> s;
    for (int n = 2; n <= N; n++){
        int p, c, cur=n;
        while (prv[cur] != 0){
            p = prv[cur];
            c = cur;
            cur = p;
            if(p > c) swap(p, c);
            s.insert((CONNECT){p, c});
        }
    }

    // 4. 정답 출력
    cout << (int)s.size() << "\n";
    for(auto c : s) cout << c.a << " " << c.b << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("../test/input.txt", "r", stdin);
    input();
    solve();
}