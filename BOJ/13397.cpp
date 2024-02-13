#include<iostream>
#define MAX 5005
#define INF 1e4
using namespace std;

int N, M;
int num[MAX];

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> num[i];
}

bool check(int val){
    
    int m = 1;
    int minVal=INF, maxVal=0, maxDiff=0;
    
    // 구간 확인
    for (int i = 0; i < N; i++){
        minVal = min(minVal, num[i]);
        maxVal = max(maxVal, num[i]);
        maxDiff = max(maxDiff, maxVal - minVal);

        if(val < maxDiff){
            m++;
            minVal = num[i];
            maxVal = num[i];
            maxDiff = 0;
        }
    }
    
    return m <= M;
}

void solve(){
    int low=0, mid, high=INF;
    while (low<=high){
        mid = (low + high) / 2;
        if(check(mid)) high = mid-1;
        else low = mid+1;
    }
    cout << low;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}