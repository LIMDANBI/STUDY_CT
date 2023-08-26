#include<iostream>
#include<cstring>
#include<vector>
#define MAX 1001
using namespace std;

int N, M, dist;
bool isfind, visited[MAX];
vector<pair<int, int>> tree[MAX];

void input(){
    cin >> N >> M;

    int a, b, d;
    for (int i = 1; i < N; i++){
        cin >> a >> b >> d;
        tree[a].push_back({b, d});
        tree[b].push_back({a, d});
    }
}

void dfs(int a, int b, int d){
    if(isfind) return;
    visited[a] = true;
    for (auto nxt : tree[a]){
        if(visited[nxt.first]) continue;
        if(nxt.first == b) {
            dist = d + nxt.second;
            isfind = true;
            return;
        }
        dfs(nxt.first, b, d+nxt.second);
    }
}

void solution(){
    int a, b;
    for (int i = 0; i < M; i++){
        cin >> a >> b;
        dist = 0; 
        isfind = false;
        memset(visited, false, sizeof(visited));
        dfs(a, b, 0);
        cout << dist << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}