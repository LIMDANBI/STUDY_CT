#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 100001
#define MAX_K 17
using namespace std;

vector<int> tree[MAX_N];

int N, M;
int depth[MAX_N];
bool visited[MAX_N];
int ancestor[MAX_K + 1][MAX_N];

void input(){
    cin >> N;

    int a, b;
    for(int i=1; i<N; i++){
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
}

void save_dapth_and_parent(int n, int d){
    visited[n] = true; // 방문
    depth[n] = d; // depth 저장
    for (int i = 0; i < tree[n].size(); i++){
        int next = tree[n][i];
        if(visited[next]) continue;
        ancestor[0][next] = n; // parent 저장
        save_dapth_and_parent(next, d + 1);
    }
}

void save_ancestor(){
    for (int k = 1; k < MAX_K; k++){ // 2^k번째 조상 노드까지 저장
        for (int n = 1; n <= N; n++)
            ancestor[k][n] = ancestor[k-1][ancestor[k-1][n]];
    }
}

int lca(int a, int b){
    if(depth[a] < depth[b]) swap(a, b); // a가 더 깊음을 보장
    for (int k = MAX_K; k >= 0; k--){ // depth 맞추기
        if(depth[a]-depth[b] >= (1<<k)) a = ancestor[k][a];
    }
    if(a==b) return a; // depth를 맞춰줬더니 LCA인 경우!

    for (int k = MAX_K; k >= 0; k--){ // LCA 찾기
        if(ancestor[k][a] != ancestor[k][b]){
            a = ancestor[k][a];
            b = ancestor[k][b];
        }
    }
    return ancestor[0][a];
}

void query(){
    cin >> M;
    int a, b;
    while(M--){
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    save_dapth_and_parent(1, 0); // root 에서 탐색 시작
    save_ancestor(); // dp를 이용한 조상 노드 저장 (2^k)
    query();
}