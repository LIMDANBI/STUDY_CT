#include<iostream>
#include<vector>
#include<queue>
#define MAX 2001
using namespace std;

struct DATA{
    int y, x, cost;

    bool operator < (const DATA &pos) const { // 연산자 오버로딩
        if(cost == pos.cost){
            if(y == pos.y) return x < pos.x;
            return y < pos.y;
        } return cost > pos.cost; // min heap
    }
};

int N, C;
int root[MAX];
priority_queue<DATA> pq;
vector<pair<int, int>> pos;

void input(){
    cin >> N >> C;

    int y, x;
    for(int i=0; i<N; i++){
        cin >> y >> x;
        pos.push_back({y, x});
        root[i] = i; // init
    }
}

void cal_cost(){
    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<N; j++){
            int cost = (pos[i].first - pos[j].first)*(pos[i].first - pos[j].first) + (pos[i].second - pos[j].second)*(pos[i].second - pos[j].second); // Euclidean distance
            if(cost < C) continue; // C 이상이 아니면 파이프 설치 거부
            pq.push({i, j, cost});
        }
    }
}

int find_(int x){
    if(root[x] == x) return x;
    return root[x] = find_(root[x]);
}

void union_(int y, int x){
    root[find_(x)] = y;
}

void kruskal(){

    int edge = 0;
    long long ans = 0;
    while(!pq.empty()){
        int y = pq.top().y;
        int x = pq.top().x;
        int cost = pq.top().cost;
        pq.pop();

        if(find_(y) != find_(x)) { // 연결되지 않은 경우
            union_(y, x);
            ans+=cost;
            edge++;
        }
    }

    if(edge == N-1) cout << ans;
    else cout << -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cal_cost(); // pos 간 cost 계산 
    kruskal(); // MST 만들기 (크루스칼 알고리즘)
}