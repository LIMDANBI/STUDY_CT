#include<iostream>
#include<algorithm>
#include<vector>
#define MAXN 100005
#define MAXH 500005
using namespace std;

int N, H;
vector<int> up, down; // 석순, 종유석

void input(){
    cin >> N >> H;
    for (int i = 0; i < N/2; i++){
        int h1, h2; cin >> h1 >> h2;
        up.push_back(h1); // 석순
        down.push_back(h2); // 종유석
    }
}

int upper_bound(int val, vector<int> &v){
    int low=0, mid, high=N/2, upper=N/2;
    while(low<=high){
        mid = (low + high)/2;
        if(val < v[mid]) {
            upper = mid;
            high = mid-1;
        }
        else low = mid+1;
    }
    return upper; // val 초과 값이 처음 등장하는 위치
}

void solve(){

    // 1. 정렬
    sort(up.begin(), up.end());
    sort(down.begin(), down.end());

    // 2. 이분 탐색
    int val = MAXH, cnt = 0;
    for(int h=1; h<=H; h++){
        int ss = upper_bound(h-1, up); // 파괴하지 않아도 되는 석순
        int jys = upper_bound(H-h, down); // 파괴하지 않아도 되는 종유석
        int destroy = N-(ss+jys); // 파괴해야하는 장애물 수
        if(destroy < val){ // (1) 개똥벌레가 파괴해야하는 장애물의 최솟값
            val = destroy;
            cnt = 1;
        }
        else if(destroy == val){ // (2) 그러한 구간이 총 몇 개 있는지
            cnt++;
        }
    }

    // 3. 정답 출력
    cout << val << " " << cnt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("../test/input.txt", "r", stdin);
    input();
    solve();
}