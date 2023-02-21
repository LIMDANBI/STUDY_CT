#include<iostream>
#define MAX 200001
using namespace std;

int N, K;
int seq[200001], cnt[100001];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    
    cin >> N >> K;
    for(int i=0; i<N; i++) cin >> seq[i];

    int left=0, right=0, ans=0;
    while(right<N){
        if(cnt[seq[right]]<K) {
            cnt[seq[right++]]++;
            ans = max(ans, right-left);
        }
        else cnt[seq[left++]]--;
    }
    cout << ans;
}