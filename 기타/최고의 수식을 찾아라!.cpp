#include<iostream>
#define MAX 7
using namespace std;

int N, A;
int W[MAX], V[MAX]; // 4개 이하 사용 시, 5개 이상 사용 시 가치

int cnt[MAX];
int ans, sol[MAX];
int sq[] = { 1, 2, 4, 8, 16, 32, 64 };

void input(){
    cin >> N;
    for (int i = 0; i < MAX; i++) cin >> W[i];
    for (int i = 0; i < MAX; i++) cin >> V[i];
    cin >> A;
}

int cal_val(){ // 수식의 가치 계산
    int res = 0, a = 0;
    for (int i = 0; i < MAX; i++){
        if(cnt[i] >= 5) res+=cnt[i]*V[i];
        else res+=cnt[i]*W[i];
        a += cnt[i];
    }
    res += (a * A);
    return res;
}

void dfs(int n, int sum){
    if(sum > N) return; // 가지치기
    if(sum == N){
        int res = cal_val();
        if(ans < res){ // 가치가 더 높은 수식인 경우 정답 갱신
            ans = res;
            for (int i = 0; i < MAX; i++) sol[i] = cnt[i];
        }
        return; 
    }

    for (int i = n; i < MAX; i++){
        cnt[i]++;
        dfs(i, sum + sq[i]);
        cnt[i]--;
    }
}

void output(){
    cout << ans << "\n";
    for (int i = 0; i < MAX; i++)
        cout << sol[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    dfs(0, 0);
    output();
}