#include<iostream>
#include<queue>
#define MAX 100001
using namespace std;

struct DATA{
    int a, b, c;
    bool operator < (const DATA &r) const { return c > r.c;}
};
priority_queue<DATA> road;

int N, M;
int parent[MAX];

int find_(int x){
    if(parent[x]==x) return x;
    return parent[x] = find_(parent[x]);
}

void union_(int x, int y){
    parent[find_(y)] = find_(x);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    int a, b, c;
    while (M--){
        cin >> a >> b >> c;
        road.push({a,b,c});
    }

    for(int i=1; i<=N; i++) parent[i] = i; // init

    int cnt=0, ans=0;
    while(!road.empty() && cnt<N-2){
        int a = road.top().a;
        int b = road.top().b;
        int c = road.top().c;
        road.pop();

        if(find_(a)!=find_(b)){
            union_(a, b);
            ans+=c;
            cnt++;
        }
    } cout << ans;
}