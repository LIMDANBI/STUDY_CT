#include<iostream>
#include<algorithm>
#define MAX 55
using namespace std;

int N; // 현재 휴게소의 개수
int M; // 더 지을 휴게소 개수
int L; // 고속 도록 길이
int restArea[MAX]; // 현재 휴게소 위치

void input(){
    cin >> N >> M >> L;
    for(int i=0; i<N; i++) cin >> restArea[i];
}

bool check(int val){
    
    int cur=0, idx=0, cnt=0;

    while (idx < N){
        while(cur+val < restArea[idx]){
            cur += val;
            cnt++;
        }
        cur = restArea[idx++];
    }

    while(cur+val < L){
        cur+=val;
        cnt++;
    }

    return cnt <= M;
}

void solve(){

    // 1. 현제 휴게소 위치 정렬
    sort(restArea, restArea+N);

    // 2. 이분 탐색
    int low=1, mid, high=L;
    while (low <= high){
        mid = (low+high)/2;
        if(check(mid)) high = mid-1;
        else low = mid+1;
    }

    // 3. 휴게소가 없는 구간의 최댓값의 최솟값
    cout << low;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}