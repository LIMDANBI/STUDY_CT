#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX 100001
using namespace std;

vector<pair<int, int>> X, Y, Z;

struct edge{
    int a, b, dist;
    bool operator < (const edge & tmp) const {
        if(dist == tmp.dist){
            if(a == tmp.a) return a > tmp.a;
            return b > tmp.b;
        } return dist > tmp.dist;
    }
};
priority_queue<edge> pq;

int N;
int root[MAX];

void input(){
    cin >> N;

    int x, y, z;
    for(int i=0; i<N; i++){
        cin >> x >> y >> z;
        X.push_back({x, i});
        Y.push_back({y, i});
        Z.push_back({z, i});
    }
}

void cal_dist(){
    
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());
    
    for(int i=0; i<N-1; i++){
        pq.push({X[i].second, X[i+1].second, X[i+1].first-X[i].first});
        pq.push({Y[i].second, Y[i+1].second, Y[i+1].first-Y[i].first});
        pq.push({Z[i].second, Z[i+1].second, Z[i+1].first-Z[i].first});
    }
}

int find(int x){
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void connect(int a, int b){
    root[find(a)] = find(b);
}

void solution(){
    
    // init
    for(int i=0; i<N; i++) root[i] = i;

    int ans = 0;
    int edgeNum = 0;
    while(edgeNum < N-1){
        int a = pq.top().a;
        int b = pq.top().b;
        int dist = pq.top().dist;
        pq.pop();

        if(find(a) != find(b)){
            connect(a, b);
            edgeNum++;
            ans += dist;
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cal_dist();
    solution();
}