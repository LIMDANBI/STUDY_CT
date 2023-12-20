#include<iostream>
#include<algorithm>
#define MAX 1001
using namespace std;

int N;
int pos[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> pos[i];
}

int lowerBound(int low, int high, int data){ // data 이상의 값이 등장하는 첫번째 위치
    int lower = MAX;
    while(low<=high){
        int mid = (low+high)/2;
        if(pos[mid] < data) low = mid+1;
        else{
            high = mid-1;
            lower = min(lower, mid);
        }
    }
    return lower;
}

int upperBound(int low, int high, int data){ // data 이하의 값 중 가장 큰 값의 위치
    int upper = -1;
    while(low<=high){
        int mid = (low+high)/2;
        if(pos[mid] > data) high = mid-1;
        else{
            low = mid+1;
            upper = max(upper, mid);
        }
    }
    return upper;
}

void solve(){
    
    // 1. 정렬
    sort(pos, pos+N);

    // 2. 도약 a -> b -> c
    int ans = 0;
    for(int a=0; a<N-2; a++){
        for(int b=a+1; b<N-1; b++){
            int diff = pos[b] - pos[a];
            int lower = lowerBound(b+1, N-1, pos[b]+diff);
            int upper = upperBound(b+1, N-1, pos[b]+diff*2);
            if(lower!=MAX && upper!=-1) ans += (upper-lower+1);
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}