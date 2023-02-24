#include<iostream>
#define MAX 1000001
using namespace std;

int N;
int A[MAX], LIS[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];
}

int lower_bound(int idx, int val){ // val 이상의 값이 등장하는 최초 위치 반환
    int res = idx;
    int lower = idx;
    int low=0, mid, high=idx;

    while(low<=high){
        mid = (low+high)/2;
        if(val <= LIS[mid]){
            high = mid-1;
            lower = min(lower, mid);
        }
        else low = mid+1;
    }
    return lower;
}

void solution(){
    int last = 0;
    LIS[0] = A[0];

    for(int i=1; i<N; i++){
        if(LIS[last] < A[i]) LIS[++last] = A[i];
        else{
            int idx = lower_bound(last, A[i]);
            LIS[idx] = A[i];
        }
    }
    cout << last+1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    input();
    solution();
}