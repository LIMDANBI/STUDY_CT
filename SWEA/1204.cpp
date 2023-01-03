#include<iostream>
#include<cstring>
#define MAX 101
using namespace std;

int cnt[MAX];

int solution(){
    int n; cin >> n;

    int score;
    memset(cnt, 0, sizeof(cnt));
    for(int i=0; i<1000; i++){
        cin >> score;
        cnt[score]++;
    }

    int ans=0, max_val=cnt[0];
    for(int i=1; i<MAX; i++) {
        if(max_val <= cnt[i]){ // 최빈수가 여러 개 일 때에는 가장 큰 점수를 출력
            max_val = cnt[i];
            ans = i;
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        cout << "#" << t << " " << solution() << "\n";
    }
}