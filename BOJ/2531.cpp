#include<iostream>
#define DISH 30001
#define KIND 3001
using namespace std;

int N, d, k, c; // 회전 초밥 벨트에 놓인 접시의 수, 초밥의 가짓수, 연속해서 먹는 접시의 수, 쿠폰 번호
int sushi[DISH], cnt[KIND];

void input(){
    cin >> N >> d >> k >> c;
    for(int i=0; i<N; i++) cin >> sushi[i];
}

void solution(){ // 주어진 회전 초밥 벨트에서 먹을 수 있는 초밥의 가짓수의 최댓값
    
    int ans = 0, kind = 1; 
    cnt[c] = 1; // coupon
    
    for(int i=0; i<k; i++){ // 처음 k개 
        if(cnt[sushi[i]] == 0) kind++;
        cnt[sushi[i]]++;
    }

    int left = 0, right = k-1; // two pointer
    while(1){

        // left
        cnt[sushi[left]]--;
        if(cnt[sushi[left]] == 0) kind--; // 종류 한 개 감소
        left++;

        //right
        right++; right%=N;
        if(right == k-1) break; // 회전 초밥 벨트 모두 확인 
        cnt[sushi[right]]++;
        if(cnt[sushi[right]] == 1) kind++; // 종류 한개 증가

        // ans update 
        ans = max(ans, kind);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    input();
    solution();
}