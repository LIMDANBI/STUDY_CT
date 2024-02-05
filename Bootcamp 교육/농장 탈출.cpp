#include<iostream>
#define MAX 25
#define SIZE 10
using namespace std;

int N;
int ans;
int W[MAX];

void input(){
    cin >> N;
    for (int i=0 ; i<N ; i++) cin >> W[i];
}

bool check(int sum, int w){
    while(sum!=0 || w!=0){
        int sr = sum%10; sum/=10;
        int wr = w%10; w/=10;
        if(sr+wr>=10) return false;
    }
    return true;
}

void dfs(int n, int idx, int cnt, int sum){

    // 1. 답 갱신
    ans = max(ans, cnt);
    
    // 2. 종료 조건
    if(N <= n) return ;

    // 3. 소 선택 (조합)
    for(int i=idx; i<N; i++){
        if(check(sum, W[i])) dfs(n+1, i+1, cnt+1, sum+W[i]);
        else dfs(n+1, i+1, cnt, sum);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(0, 0, 0, 0);
    cout << ans;
}