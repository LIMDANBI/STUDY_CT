#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;

int N;
int parent[MAX];
vector<int> tree[MAX];

void input(){
    cin >> N;

    int a, b;
    for(int i=0; i<N; i++){
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
}

void find_parent(int node, int prev){
    parent[node] = prev;
    for(int i=0; i<tree[node].size(); i++){
        int next = tree[node][i];
        if(parent[next]) continue;
        find_parent(next, node); 
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    find_parent(1, 1);
    for(int i=2; i<=N; i++) cout << parent[i] << "\n";
}