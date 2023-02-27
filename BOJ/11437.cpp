#include<iostream>
#include<vector>
#define MAX 50001
using namespace std;

int N, M;
int depth[MAX];
int parent[MAX];
vector<int> tree[MAX];

void input(){
    cin >> N;

    int a, b;
    for(int i=1; i<N; i++){
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a); // tree는 양방향
    }
}

void get_depth_and_parent(int n, int d){
    depth[n] = d;
    for(int i=0; i<tree[n].size(); i++){
        int next = tree[n][i];
        if(depth[next]) continue;
        parent[next] = n; 
        get_depth_and_parent(next, d+1);
    } 
}

void solution(){
    get_depth_and_parent(1, 1); // 각 node의 depth, parent를 구함

    cin >> M;
    int y, x, tmp;
    for(int i=0; i<M; i++){
        cin >> y >> x;
        
        if(depth[y] < depth[x]) { // y 가 더 깊음을 보장
            tmp = y;
            y = x;
            x = tmp;
        }
        while(depth[y]!=depth[x]) y = parent[y];
        while(y!=x) {
            y = parent[y];
            x = parent[x];
        }
        cout << y << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    input();
    solution();
}