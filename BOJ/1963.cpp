#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#define MAX 10000
using namespace std;

struct DATA{int num, cnt;};

int arr[4];
bool visited[MAX];
bool notPrime[MAX];

void eratosthenes(){
    for (int a=2; a*a<MAX; a++){
        if(notPrime[a]) continue;
        for (int b=a+a; b<MAX; b+=a) {
            notPrime[b] = true;
        }
    }
}

void int_to_arr(int a){
    for (int idx = 3; idx >= 0; idx--){
        arr[idx] = a % 10;
        a /= 10;
    }
}

int arr_to_int(){
    return (arr[0] * 1000 + arr[1] * 100 + arr[2] * 10 + arr[3]);
}

int bfs(int s, int e){

    // 1. 초기화
    memset(visited, false, sizeof(visited));

    // 2. 시작점 처리
    queue<DATA> q;
    q.push({s, 0});
    visited[s] = true;

    // 3. bfs
    while (!q.empty()){
        int num = q.front().num; 
        int cnt = q.front().cnt;
        int_to_arr(num); // 현재 수
        q.pop();

        if(num == e) return cnt;
        for (int idx = 0; idx < 4; idx++){
            int tmp = arr[idx]; // 저장
            for (int n = 0; n < 10; n++){
                arr[idx] = n;
                int val = arr_to_int();
                if(val<1000 || notPrime[val] || visited[val]) continue;
                q.push({val, cnt+1});
                visited[val] = true;
            }
            arr[idx] = tmp; // 복원
        }
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T, s, e, ans; cin >> T;
    eratosthenes(); // 에라토스테네스의 체
    while(T--){
        cin >> s >> e;
        ans = bfs(s, e);
        if(ans == -1) cout << "Impossible\n";
        else cout << ans << "\n";
    }
}