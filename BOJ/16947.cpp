#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 3005
using namespace std;

struct QUEUE{ int n, d; };

int N;
bool isFind; // cycle을 찾았는지
int pre[MAX]; // 이전 역
int dist[MAX]; // 순환선과의 거리
bool cycle[MAX]; // 순환선 여부
bool visited[MAX];
vector<int> station[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        station[a].push_back(b);
        station[b].push_back(a); // 양방향
    }
}

void find_cycle(int cur){
    visited[cur] = true;
    for(int nxt : station[cur]){
        if(isFind) return;
        if(visited[nxt]){
            if(nxt != pre[cur]){ // cycle을 찾은 경우
                isFind = true;
                cycle[cur] = true;

                int tmp = cur;
                while (tmp != nxt){ // cycle 역 추적
                    cycle[pre[tmp]] = true;
                    tmp = pre[tmp];
                }
            }
        }
        else{
            pre[nxt] = cur;
            find_cycle(nxt);
        }
    }
}

void get_dist(){

    // 1. 초기화
    memset(visited, false, sizeof(visited));

    // 2. 시작점 처리
    queue<QUEUE> q;
    for (int n = 1; n <= N; n++){
        if(cycle[n]) {
            visited[n] = true;
            q.push((QUEUE){n, 0});
        }
    }

    // 3. bfs
    while (!q.empty()){
        int n = q.front().n;
        int d = q.front().d;
        q.pop();

        for(int nxt : station[n]){
            if(visited[nxt]) continue;
            visited[nxt] = true;
            q.push((QUEUE){nxt, d + 1});
            dist[nxt] = d + 1;
        }
    }
}

void output(){
    for (int n = 1; n <= N; n++)
        cout << dist[n] << " ";
}

void solve(){
    
    // 1. 순환 노선 찾기
    find_cycle(1);

    // 2. n번 역과 순환선 사이 거리 구하기
    get_dist();

    // 3. n번 역과 순환선 사이 거리 출력
    output();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("../test/input.txt", "r", stdin);
    input();
    solve();
}