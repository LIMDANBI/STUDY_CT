#include<iostream>
#include<algorithm>
#include<string>
#define MAX 100005
using namespace std;

struct FLOWER{
    int open, close;
    bool operator < (const FLOWER &f) const{
        return open < f.open; // 빨리 피는 순으로 정렬
    }
};
FLOWER flower[MAX];

int N;

void input(){
    cin >> N;
    int om, od, cm, cd;
    for(int i=0; i<N; i++){
        cin >> om >> od >> cm >> cd;
        flower[i] = {om*100+od, cm*100+cd};
    }
}

void solve(){

    // 1. 오름차순 정렬
    sort(flower, flower+N);

    // 2. 꽃 확인
    int ans = 0;
    int last = 301;
    for(int i=0; i<N && last<=1130; i++){
        int maxLast = 0;
        for(int j=i; j<N; j++){
            if(flower[j].open <= last){
                maxLast = max(flower[j].close, maxLast);
            }
            else break;
        }
        if(maxLast==0){
            ans = 0;
            break;
        }
        last = maxLast;
        ans++;
    }
    if(last < 1201) ans = 0;
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}