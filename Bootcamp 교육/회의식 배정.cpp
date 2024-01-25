#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct MEETING{
    int n, s, e;
    bool operator < (const MEETING &m) const{
        if(e == m.e) return s < m.s;
        return e < m.e;
    }
};

int N;
vector<MEETING> meeting;

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        int n, s, e;
        cin >> n >> s >> e;
        meeting.push_back({n, s, e});
    }
}

void solve(){
    int prv = 0; // 이전 종료 시간
    int cnt = 0; // 배정 가능한 최대 회의 수
    vector<int> nums; // 배정 가능한 회의 번호

    // 1. 회의 종료 시간을 기준으로 정렬
    sort(meeting.begin(), meeting.end());

    // 2. 그리디하게 회의 배정
    for(auto m : meeting){
        if(m.s >= prv){
            nums.push_back(m.n);
            prv = m.e;
            cnt++;
        }
    }

    // 3. 정답 출력
    cout << cnt << "\n";
    for(int n : nums) cout << n << " ";
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}