#include<iostream>
#include<algorithm>
#define MAX 10001
using namespace std;

int N, M;
int upper;
int budget[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> budget[i];
        upper = max(upper, budget[i]);
    }
    cin >> M;
}

bool check(int val){ // cost로 예산 배정이 가능한지
    int sum = 0;
    for(int i=0; i<N; i++) sum += min(val, budget[i]);
    return sum <= M;
}

void solve(){
    int low=0, mid, high=upper;
    while(low<=high){
        mid=(low+high)/2;
        if(check(mid)) low = mid+1;
        else high = mid-1;
    }
    cout << high;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}