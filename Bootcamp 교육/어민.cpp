#include<iostream>
#define MAX 100005
#define INF 1000000005
using namespace std;

int N; // 마을 수
int A[MAX]; // 마을 위치
int B[MAX]; // 잡힌 물고기 양

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i] >> B[i];
}

bool check(int val){
    long long cnt = 0;
    for(int i=0; i<N; i++){
        int tax = A[i+1]-A[i]; // 세금
        cnt += (B[i] - val); // 필요한 물고기
        if(cnt < 0 && i!=N-1){ // 물고기가 부족한 경우, 다음 마을에서 빌려옴
            cnt -= tax;
        }
        else if(i!=N-1){ // 물고기가 남는 경우, 다음 마을에 넘겨줌
            cnt = max((long long)0, (cnt-tax));
        }
    }
    if(cnt < 0) return false;
    return true;
}

void solve(){ // 각 마을에 동일한 수로 입양될 수 있는 최대 아이들 수
    int low=0, mid, high=INF;
    while (low<=high){
        mid = (low+high)/2;
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