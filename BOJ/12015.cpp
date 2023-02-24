#include<iostream>
#define MAX 1000001
using namespace std;

int N;
int A[MAX];
int LIS[MAX]; // 가장 긴 증가하는 부분 수열

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];
}

int lower_bound(int idx, int target){ // target 이상의 값이 등장하는 최초 위치 반환
    int res = idx;
    int low=0, mid, high=idx;
    while(low <= high){
        mid = (low+high)/2;
        if(target <= LIS[mid]){
            high = mid-1;
            res = min(res, mid);
        }
        else low = mid+1;
    }
    return res;
}

void solution(){

    int last = 0; // ans 이자 idx
    LIS[0] = A[0];

    for(int i=1; i<N; i++){
        if(LIS[last] < A[i]) LIS[++last] = A[i];
        else{
            int idx = lower_bound(last, A[i]); // LIS는 정렬된 수열
            LIS[idx] = A[i];
        }
    }
    cout << last + 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    input();
    solution();
}