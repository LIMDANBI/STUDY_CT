#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 10001
using namespace std;

int V, E, a, b;
int depth[MAX];
int parent[MAX];
bool visited[MAX];
vector<int> tree[MAX];

void input(){
    cin >> V >> E >> a >> b;

    int p, c;
    for(int i=0; i<E; i++){
        cin >> p >> c;
        tree[p].push_back(c);
        tree[c].push_back(p);
    }
}

void init(){
    for(int i=0; i<MAX; i++) tree[i].clear();
    memset(visited, false, sizeof(visited));
}

void dfs(int node, int cnt){
    depth[node] = cnt;
    visited[node] = true;
    for(int i=0; i<tree[node].size(); i++){
        int next = tree[node][i];
        if(visited[next]) continue;
        parent[next] = node; // 부모 정보 저장
        dfs(next, cnt+1);
    }
}

void solution(int t){

    dfs(1, 0);
    
    int lca, sub_size=1;

    while(a!=b){ // 공통 조상을 찾음
        if(depth[a] == depth[b]){
            a = parent[a];
            b = parent[b];
        }
        else if(depth[a] < depth[b]) b = parent[b];
        else a = parent[a];
    }
    lca = a;

    queue<int> q;
    q.push(a);
    
    while(!q.empty()){ // sub tree 크기 구하기
        int n = q.front();
        q.pop();
        for(int i=0; i<tree[n].size(); i++){
            if(tree[n][i] == parent[n]) continue;
            q.push(tree[n][i]);
            sub_size++;
        }
    }
    cout << "#" << t << " " << lca << " " << sub_size << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        init();
        input();
        solution(t);
    }
}