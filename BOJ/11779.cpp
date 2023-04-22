#include<iostream>
#include<vector>
#include<queue>
#define MAX 1001
#define INF 100000001
using namespace std;

struct BUS {int next, cost;};
struct DATA {
    int cost, node;
    bool operator < (const DATA &d) const {
        return cost > d.cost;
    }
};

int N, M;
int dist[MAX];
int path[MAX];
bool visited[MAX];
vector<BUS> v[MAX];

void input(){
    cin >> N >> M;

    int a, b, c;
    while (M--) {
        cin >> a >> b >> c;
        v[a].push_back({b, c});
    }
}

void solution(){
    int s, e; cin >> s >> e;
    for (int i = 1; i <= N; i++) dist[i] = INF;

    priority_queue<DATA> pq;
    pq.push({0, s});
    dist[s] = 0;

    while (!pq.empty()){
        int node = pq.top().node;
        pq.pop();

        if(visited[node]) continue;
        visited[node] = true;

        for (int i = 0; i < v[node].size(); i++){
            int next = v[node][i].next;
            int new_cost = dist[node] + v[node][i].cost;
            if(new_cost < dist[next]){
                path[next] = node;
                dist[next] = new_cost;
                pq.push({new_cost, next});
            }
        }
    }

    vector<int> pathNode;
    int cnt = 0, tmp = e;
    while (tmp != 0) {
        cnt++;
        pathNode.push_back(tmp);
        tmp = path[tmp];
    }

    // output
    cout << dist[e] << "\n" << cnt << "\n";
    for (int i = pathNode.size() - 1; i >= 0; i--) cout << pathNode[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}