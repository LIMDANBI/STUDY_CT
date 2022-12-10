#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

int N;
int a, b; // 촌수를 계산해야 하는 서로 다른 두 사람
int ans = 0; // 두 사람의 촌수
bool visited[MAX];
vector<int> v[MAX];

void input(){
    cin >> N;
    cin >> a >> b;
    cin >> N;
    int x, y;
    while(N--){
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
}

void dfs(int node, int cnt){
    visited[node] = true;
    if(node == b) ans = cnt;
    for(int i=0; i<v[node].size(); i++){
        int next = v[node][i];
        if(visited[next]) continue;
        dfs(next, cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(a, 0);
    ans == 0 ? cout << -1 : cout << ans;
}