#include<iostream>
#include<queue>
#define MAX 1005
using namespace std;

struct LINE{
    int a, b, c;
    bool operator < (const LINE &l) const {
        return c > l.c; // 오름차순 정렬
    }
};

int N; // 컴퓨터 수
int M; // 연결할 수 있는 선 수
int root[MAX];
priority_queue<LINE> pq; // a, b 컴퓨터를 연결하는데 드는 비용 c

void input(){
    cin >> N;
    cin >> M;

    int a, b, c;
    for (int i = 0; i < M; i++){
        cin >> a >> b >> c;
        pq.push((LINE){a, b, c});
    }
}

int Find(int x){
    if(root[x] == x) return x;
    return root[x] = Find(root[x]);
}

void Union(int x, int y){
    root[Find(x)] = root[Find(y)];
}

void solve(){

    int ans=0, cnt=0;

    for(int i=1; i<=N; i++){
        root[i] = i;
    }

    // MST 만들기
    while(cnt!=N-1){
        int a = pq.top().a;
        int b = pq.top().b;
        int c = pq.top().c;
        pq.pop();

        if(Find(a) != Find(b)){
            Union(a, b);
            ans += c;
            cnt++;
        }
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}