#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#define MAX 101
using namespace std;

struct POS{double y, x;};
struct STAR{
    int a, b;
    double c;
    bool operator < (const STAR &s) const{
        return c > s.c;
    }
};
vector<POS> v;
priority_queue<STAR> pq;

int N;
int parent[MAX];

void input(){
    cin >> N;

    double y, x, c;
    for(int a=0; a<N; a++){
        cin >> y >> x;
        for(int b=0; b<a; b++){
            c = sqrt(pow(abs(v[b].y-y),2) + pow(abs(v[b].x-x),2));
            pq.push({a, b, c});
        }
        v.push_back({y, x});
    }
}

int find_(int a){
    if(a==parent[a]) return a;
    return parent[a] = find_(parent[a]);
}

void union_(int a, int b){
    parent[find_(b)] = find_(a);
}

void solution(){
    for(int i=0; i<N; i++) parent[i] = i;

    int cnt=0;
    double ans=0;
    while(!pq.empty() && cnt<N-1){
        int a = pq.top().a;
        int b = pq.top().b;
        double c = pq.top().c;
        pq.pop();

        if(find_(a)!=find_(b)){
            union_(a, b);
            cnt++;
            ans+=c;
        }
    }
    cout << fixed; 
    cout.precision(2);
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}