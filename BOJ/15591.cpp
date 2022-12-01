#include <iostream>
#include <vector>
#define MAX 5001
#define INF 1000000001
using namespace std;

int N, Q;
int USADO[MAX];
bool visited[MAX];
vector<pair<int, int> > path[MAX];

void input(){
    cin >> N >> Q;

    int p, q, r;
    for(int i=1; i<N; i++){
        cin >> p >> q >> r;
        path[p].push_back({q, r});
        path[q].push_back({p, r});
    }
}

void init(){
    for(int i=1; i<=N; i++){
        USADO[i] = INF;
        visited[i] = false;
    }
}

void find_min_val(int node, int min_cost){
    visited[node] = true;
    for(int i=0; i<path[node].size(); i++){
        int next_node = path[node][i].first;
        int next_cost = path[node][i].second;
        if(visited[next_node]) continue;
        USADO[next_node] = min(min(min_cost, next_cost), USADO[next_node]);
        find_min_val(next_node, USADO[next_node]);
    }
}

void output(int k){
    int ans = 0;
    for(int i=1; i<=N; i++){
        if(USADO[i]>=k) ans++;
    }
    cout << ans << "\n";
}

void solution(){
    int k, v;
    while (Q--){
        cin >> k >> v;
        init();
        USADO[v] = 0;
        find_min_val(v, INF);
        output(k);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}