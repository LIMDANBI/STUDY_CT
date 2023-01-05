#include<iostream>
#include<cstring>
#define MAX 10
using namespace std;

int N;
int ans;
int total;
int weight[MAX];
bool isuse[MAX];

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

// 오른쪽 위에 올라가 있는 무게의 총합이 왼쪽에 올라가 있는 무게의 총합보다 더 커져서는 안 됨
void dfs(int cnt, int left, int right){ 

    if(cnt == N){ // 모든 무게추를 올린 경우
        ans++;
        return;
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