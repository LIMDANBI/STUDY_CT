#include<iostream>
#define MAX 300005
using namespace std;

int N, K;
int len[MAX]; // 이름 길이
int cnt[MAX]; // 이름 길이 학생 수

void input(){
    cin >> N >> K;
    
    string name;
    for(int i=0; i<N; i++){
        cin >> name;
        len[i] = name.size();
    }
}

void solve(){
    
    long long ans = 0; // '베프' 쌍의 수

    // 1. 처음 k 명
    for(int i=0; i<=K; i++) cnt[len[i]]++;

    // 2. 슬라이딩 윈도우
    int r = K+1; 
    for(int l=0; l<N; l++){
        ans += (cnt[len[l]]-1); // 본인과 이름 길이가 같은 학생 수
        cnt[len[l]]--; // 다음 학생을 봄
        if(r < N) cnt[len[r++]]++; // 학생이 더 있는 경우
    }

    // 3. 정답 출력
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}