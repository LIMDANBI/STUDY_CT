#include<iostream>
#define MAX 100001
using namespace std;

int N, S;
int num[MAX];

void input(){
    cin >> N >> S;
    for(int i=0; i<N; i++) cin >> num[i];
}

void solution(){
    int ans = MAX;
    int l=0, r=0, sum=num[0];

    while(1){
        if(S <= sum){
            ans = min(ans, r-l+1);
            sum -= num[l++];
            if(N-1 < l) break;
        }
        else{
            r++;
            if(N-1 < r) break;
            sum += num[r];
        }
    }
    if(ans == MAX) cout << 0;
    else cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}