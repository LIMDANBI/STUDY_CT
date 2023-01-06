#include<iostream>
#include<cstring>
#include<vector>
#define MAX 11
#define INF 100000001
using namespace std;

int N;
int ans;
int cy, cx, hy, hx;
bool visited[MAX];
vector<pair<int, int> > pos;

void init(){
    ans = INF;
    pos.clear();
    memset(visited, false, sizeof(visited));
}

void input(){
    cin >> N;
    cin >> cy >> cx; // 회사의 좌표
    cin >> hy >> hx; // 집의 좌표
    
    int y, x;
    for(int i=0; i<N; i++){ // N명의 고객의 좌표
        cin >> y >> x;
        pos.push_back({y, x});
    }
}

void solution(int cnt, int y, int x, int cost){
    if(cost > ans) return; // 더 이상 볼 필요 x

    if(cnt == N){
        cost += abs(hy-y)+abs(hx-x); // 집으로
        ans = min(ans, cost);
        return;
    }
    
    for(int i=0; i<N; i++){
        if(visited[i]) continue;
        visited[i] = true;
        int new_cost = cost + abs(y-pos[i].first) + abs(x-pos[i].second);
        solution(cnt+1, pos[i].first, pos[i].second, new_cost);
        visited[i] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        init();
        input();
        solution(0, cy, cx, 0); // 회사에서
        cout << "#" << t << " " << ans << "\n";
    }
}