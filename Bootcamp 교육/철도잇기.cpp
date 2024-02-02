#include<iostream>
#include<algorithm>
#include<queue>
#define MAX 55
using namespace std;

int N, M, K;
bool check[MAX];
vector<int> v[MAX];

void input(){
    cin >> N >> M >> K;
    
    int a, b;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
}

bool comp(int a, int b){
    return a > b;
}

int bfs(int n){
    
    int res = 1;

    // 1. 시작점 처리
    queue<int> q;
    q.push(n);
    check[n] = true;

    // 2. bfs
    while(!q.empty()){
        n = q.front();
        q.pop();

        for(auto nxt : v[n]){
            if(check[nxt]) continue;
            check[nxt] = true;
            q.push(nxt);
            res++;
        }
    }

    return res;
}

void solve(){ // 최대 연결되는 도시의 수

    int ans = 0;
    vector<int> csize;

    // 1. 현재 연결된 도시들 구하기
    for(int n=1; n<=N; n++){
        if(check[n]) continue;
        csize.push_back(bfs(n));
    }

    // 2. 내림차순 정렬
    sort(csize.begin(), csize.end(), comp);

    // 3. 가장 많은 개수의 도시 연결
    for(auto s : csize){
        ans += s;
        if(--K<0) break;
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}