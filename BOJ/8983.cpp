#include<iostream>
#include<algorithm>
#define MAX 100001
using namespace std;

struct ANIMAL{int a, b;};

int M, N, L;
int gun[MAX];
ANIMAL animal[MAX];

void input(){
    cin >> M >> N >> L;
    for(int i=0; i<M; i++) cin >> gun[i];
    for(int i=0; i<N; i++) cin >> animal[i].a >> animal[i].b;
}

int upperBound(int x){ // x 이하 중 최대를 찾음 (사대)
    int upper = -1;
    int low=0, mid, high=M-1;
    while(low <= high){
        mid = (low+high)/2;
        if(gun[mid] <= x){
            upper = mid;
            low = mid+1;
        }
        else high = mid-1;
    }
    return upper;
}

void solve(){
    int ans = 0;

    // 1. 사대 정렬
    sort(gun, gun+M);

    // 2. 동물을 기준으로 사대를 본다.
    for(int i=0; i<N; i++){
        int low = animal[i].a + animal[i].b - L; // i번 동물을 잡을 수 있는 사대 (하한)
        int high = L + animal[i].a - animal[i].b;  // i번 동물을 잡을 수 있는 사대 (상한)
        int upper = upperBound(high);
        if(upper!=-1 && low<=gun[upper]) ans++;
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}