#include<iostream>
#include<cstring>
#define MAX 10
using namespace std;

int N;
int ans;
int total;
int weight[MAX];
bool isuse[MAX];
int exponential[MAX] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
int factorial[MAX] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

void init(){
    ans = 0;
    total = 0;
    memset(isuse, false, sizeof(isuse));
}

void input(){
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> weight[i];
        total+=weight[i];
    }
}

void dfs(int cnt, int left, int right){ // 오른쪽 <= 왼쪽

    if(cnt == N){ // 모든 무게추를 올린 경우
        ans++;
        return;
    }

    if(total-left <= left){ // 추를 올리는 경우의 수 (시간 초과 방지,,)
        ans += exponential[N-cnt] * factorial[N-cnt];
        return ;
    }

    for(int i=0; i<N; i++){
        if(isuse[i]) continue;
        isuse[i] = true;
        dfs(cnt+1, left+weight[i], right);
        if(right+weight[i] <= left) dfs(cnt+1, left, right+weight[i]);
        isuse[i] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        init();
        input();
        dfs(0, 0, 0);
        cout << "#" << t << " " << ans << "\n"; 
    }
}