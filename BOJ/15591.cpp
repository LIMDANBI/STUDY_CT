#include <iostream>
#include <vector>
#include <queue>
#define MAX 5001
#define INF 1000000001
using namespace std;

int N, Q;
bool visited[MAX];
vector<pair<int, int> > path[MAX];

void input(){
    cin >> N >> Q;

    int p, q, r;
    for(int i=1; i<N; i++){ // 양방향 그래프
        cin >> p >> q >> r;
        path[p].push_back({q, r});
        path[q].push_back({p, r});
    }
}

void bfs(int k, int v){
    for(int i=1; i<=N; i++) visited[i] = false;
    visited[v] = true;

    int ans = 0;

    queue<int> q;
    q.push(v);

    while (!q.empty()){
        int now_node = q.front();
        q.pop();

        for(int i=0; i<path[now_node].size(); i++){
            int next_node = path[now_node][i].first;
            int next_dist = path[now_node][i].second;

            if(visited[next_node]) continue;
            if(next_dist < k) continue;
            
            ans++;
            visited[next_node] = true;
            q.push(next_node);
        }
    }
    cout << ans << "\n";
}

void solution(){
    int k, v;
    while (Q--){
        cin >> k >> v;
        bfs(k, v);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}