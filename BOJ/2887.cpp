#include<iostream>
#include<vector>
#include<queue>
#define MAX 100001
using namespace std;

struct pos{ int x, y, z;};
vector<pos> planet;

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
        planet.push_back({x,y,z});
    }
}

void cal_min_dist(){
    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<N; j++){
            int dist = min(abs(planet[i].x-planet[j].x), min(abs(planet[i].y-planet[j].y), abs(planet[i].z-planet[j].z)));
            pq.push({i, j, dist});
        }
    }
}

int find(int x){
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void connect(int a, int b){
    root[find(a)] = b;
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
    cal_min_dist();
    solution();
}