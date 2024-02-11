#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 300005
using namespace std;

struct GROUP{
    int idx, diff;
    bool operator < (const GROUP &g) const{
        return diff > g.diff; // 내림차순 정렬
    }
};

int N, K;
int H[MAX];
GROUP D[MAX];

void input(){
    cin >> N >> K;
    for(int i=0; i<N; i++) cin >> H[i];
}

void solve(){

    // 1. 원생 간의 차이 구하기
    for(int i=1; i<N; i++){
        D[i-1] = {i-1, H[i]-H[i-1]}; 
    }

    // 2. 차이 내림차순으로 정렬
    sort(D, D+N);

    // 3. K-1개의 가장 큰 차이가 나는 구간으로 조 나누기
    vector<int> idxs;
    for(int i=1; i<K; i++){
        idxs.push_back(D[i-1].idx);
    }
    sort(idxs.begin(), idxs.end());

    // 4. K개의 조로 나누었을 때, 티셔츠 만드는 비용
    int ans=0, prv=0;
    for(auto idx : idxs){
        ans += (H[idx]-H[prv]);
        prv = idx+1;
    }
    ans += H[N-1]-H[prv];

    // 5. 티셔츠를 만드는 최소 비용 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}