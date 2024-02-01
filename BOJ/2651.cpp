#include<iostream>
#include<deque>
#include<queue>
#define MAX 105
#define INF (0x7fffffff)
using namespace std;

struct DATA{int prv, remain;};

int L; // 정비를 받지 않고 갈수있는 최대거리
int N; // 정비소 개수
int pnum[MAX]; // 이전 정비소 번호
int dist[MAX]; // 정비소사이거리
int times[MAX]; // 정비시간
int vtimes[MAX]; // 총 정비 시간

void init(){
    for(int i=0; i<MAX; i++) vtimes[i] = INF;
}

void input(){
    cin >> L >> N;
    for (int i=1; i<=N+1; i++) cin >> dist[i];
    for (int i=1; i<=N; i++) cin >> times[i];
}

void solve(int dest){

    // 1. 초기화 및 시작점 처리
    queue<DATA> q;
    vtimes[0] = 0;
    q.push({0, L});

    // 2. BFS
    while (!q.empty()){
        int prv = q.front().prv;
        int remain = q.front().remain;
        q.pop();

        int cumul = 0;
        for(int nxt=prv+1; nxt<=dest; nxt++){
            cumul += dist[nxt];
            if(remain < cumul) break; // 해당 정비소에 도착할 수 없는 경우
            
            int prvTime = vtimes[nxt];
            int newTime = vtimes[prv] + times[nxt];
            int newRemain = remain - cumul;

            if(newTime <= prvTime){ // 더 작은 시간으로 도착할 수 있는 경우
                pnum[nxt] = prv;
                q.push({nxt, L});
                vtimes[nxt] = newTime;
            }
        }
    }
}

void output(int dest){

    // 1. 총 정비 시간
    cout << vtimes[dest] << "\n";

    // 방문한 정비소 번호 역 추적하기
    int cur = dest;
    deque<int> path;
    while(pnum[cur]){
        path.push_front(pnum[cur]);
        cur = pnum[cur];
    }

    // 2. 방문하는 정비소의 개수
    cout << (int)path.size() << "\n";

    // 3. 방문한 정비소 번호
    for(auto n : path) cout << n << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solve(N+1);
    output(N+1);
}