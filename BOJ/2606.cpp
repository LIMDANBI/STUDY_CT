#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

int N, M;
int ans = 0;
bool visited[MAX];
vector<int> v[MAX];

void input(){ 
    cin >> N >> M;

    int a, b;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
}

void dfs(int node){
    visited[node] = true;
    for(int i=0; i<v[node].size(); i++){
        int next = v[node][i];
        if(visited[next]) continue;
        ans++;
        dfs(next);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(1);
    cout << ans;
}