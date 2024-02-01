#include <iostream>
#include <vector>
#include <queue>
#define MAX 10005
#define SIZE 150
#define INF 1e9
using namespace std;

struct PQ{
    int d; char prv, cur;
    bool operator < (const PQ &info) const{
        return d > info.d; // min heap
    }
};
priority_queue<PQ> pq;

struct DATA{int cost, nxt;};
vector<DATA> edge[SIZE]; // A(65), a(97)

int P;
int dist[MAX];

void init(){
    for(int i=0; i<MAX; i++) dist[i] = INF;
}

void input(){
    cin >> P;
    char n1, n2; // 목장 번호
    int d; // 거리
    for (int i=0; i<P; i++){
        cin >> n1 >> n2 >> d;

        // 길 정보 저장
        edge[n1].push_back({d, n2});
        edge[n2].push_back({d, n1});

        // 출발점 저장
        if('A'<=n1 && n1<='Y') {
            dist[n1] = 0;
            pq.push({0, n1, n1});
        }
        if('A'<=n2 && n2<='Y') {
            dist[n2] = 0;
            pq.push({0, n2, n2});
        }
    }
}

void solve(){

    char cn = '.'; // 원래 있던 목장의 번호
    int cd = INF; // 소가 걷는 거리

    while(!pq.empty()){
        int d = pq.top().d;
        char prv = pq.top().prv;
        char cur = pq.top().cur;
        pq.pop();

        // 헛간에 도착한 경우
        if(cur == 'Z' && d < cd){
            cn = prv;
            cd = d;
        }

        // 다음 방문지
        for(auto e : edge[cur]){
            char nxt = e.nxt;
            int cost = dist[cur] + e.cost;
            if(cost < dist[nxt]){
                pq.push({cost, prv, nxt});
                dist[nxt] = cost;
            }
        }
    }

    cout << cn << " " << cd << "\n";
}

int main(){
    init();
    input();
    solve();
}