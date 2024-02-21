#include<iostream>
#include<queue>
#define MAX 100001
using namespace std;

int N, K;
int cost[MAX];

void input(){
    cin >> N >> K;
}

void solve(){

    if(N==K){ // 둘의 시작 위치가 같은 경우
        cout << 0 << "\n" << 1;
        return;
    }

    // 1. 초기화
    int cnt = 0; // 방법 개수
    for (int i = 0; i < MAX; i++) cost[i] = MAX; // 가장 빠르게 찾을 수 있는 시간

    // 2. 시작점 처리
    queue<int> q;
    cost[N] = 0;
    q.push(N);

    // 3. bfs
    while (!q.empty()){
        int cur = q.front();
        q.pop();

        // 앞으로 걷기
        if(cur+1<MAX && cost[cur]+1<=cost[cur+1]){
            cost[cur + 1] = cost[cur] + 1;
            if(cur+1==K) cost[cur]+1 == cost[cur+1] ? cnt++ : cnt=1;
            else q.push(cur + 1);
        }

        // 뒤로 걷기
        if(0<=cur-1 && cost[cur]+1<=cost[cur-1]){
            cost[cur - 1] = cost[cur] + 1;
            if(cur-1==K) cost[cur]+1 == cost[cur-1] ? cnt++ : cnt=1;
            else q.push(cur - 1);
        }

        // 순간이동
        if(cur*2<MAX && cost[cur]+1<=cost[cur*2]){
            cost[cur * 2] = cost[cur] + 1;
            if(cur*2==K) cost[cur]+1 == cost[cur*2] ? cnt++ : cnt=1;
            else q.push(cur * 2);
        }
    }

    // 4. 정답 출력
    cout << cost[K] << "\n" << cnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("../test/input.txt", "r", stdin);
    input();
    solve();
}