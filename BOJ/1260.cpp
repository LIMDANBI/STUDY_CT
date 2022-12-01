#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX 1001
using namespace std;

int N, M, V;
bool visited[MAX];
vector<int> graph[MAX];

void input(){
    cin >> N >> M >> V;

    int a, b;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문
    for(int i=1; i<=N; i++) sort(graph[i].begin(), graph[i].end());
}

void dfs(int node){
    visited[node] = true;
    cout << node << " ";

    for(int i=0; i<graph[node].size(); i++){
        int next_node = graph[node][i];
        if(visited[next_node]) continue;
        dfs(next_node);
    }
}

void bfs(){
    for(int i=0; i<=N; i++) visited[i] = false;
    visited[V] = true;

    queue<int> q;
    q.push(V);

    while(!q.empty()){
        int node = q.front();
        cout << node << " ";
        q.pop();

        for(int i=0; i<graph[node].size(); i++){
            int next_node = graph[node][i];
            if(visited[next_node]) continue;
            visited[next_node] = true;
            q.push(next_node);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(V);
    cout << "\n";
    bfs();
}