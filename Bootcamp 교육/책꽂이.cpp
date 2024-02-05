#include<iostream>
#define MAX 25
#define INF 1e9
using namespace std;

int N, B; // 소 마리 수, 책꽂이 높이
int ans;
int H[MAX];

void input(){
    cin >> N >> B;
    for (int i=0; i<N; i++) cin >> H[i];
}

void dfs(int idx, int sum){
    if(ans <= sum) return;
    if(idx == N){
        if(B <= sum) ans = sum;
        return;
    }

    // 해당 소를 선택 X    
    dfs(idx+1, sum);

    // 해당 소를 선택
    dfs(idx+1, sum+H[idx]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        ans = INF;
        input();
        dfs(0, 0);
        ans-=B;
        cout << ans << "\n";
    }
}