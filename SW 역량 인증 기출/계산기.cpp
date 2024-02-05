#include<iostream>
#include<string>
#include<algorithm>
#define MAX 205
using namespace std;

int B; // 진법
int val[MAX];
string S, D; // 두 정수

void input(){
    cin >> B >> S >> D;
}

void solve(){

    // 1. S의 길이가 더 긺을 보장
    if(S.size() < D.size())
        swap(S, D);
    
    // 2. 부호 처리
    string sign="";
    if((S[0]=='-' && D[0]!='-') || (S[0]!='-' && D[0]=='-'))
        sign = "-";
    if(S[0] == '-') S = S.substr(1);
    if(D[0] == '-') D = D.substr(1);

    // 3. 초기화
    for (int i = 0; i < MAX; i++)
        val[i] = 0;

    // 3. 곱셈 (손으로 하듯이)
    int dsize = (int)D.size();
    int ssize = (int)S.size();

    int a, b, mul;
    for (int d = 0; d < dsize; d++){
        for (int s = 0; s < ssize; s++){
            'A' <= D[dsize-d-1] ? a = D[dsize-d-1]-'A'+10 : a = D[dsize-d-1]-'0';
            'A' <= S[ssize-s-1] ? b = S[ssize-s-1]-'A'+10 : b = S[ssize-s-1]-'0';
            mul = a*b + val[d+s];
            val[d+s+1] += mul/B; // 올림
            val[d+s] = mul%B; // 나머지
        }
    }

    // 4. 곱셈 결과 출력
    string ans = "";
    bool start = false;
    for (int i = MAX-1; i >= 0; i--){
        if(val[i]!=0) start = true;
        if(!start && val[i]==0) continue;
        if(val[i] < 10) ans += (char)(val[i]+'0');
        else ans += (char)(val[i]+'A'-10);
    }
    if(ans == "") cout << "0\n";
    else cout << sign << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin >> TC;
    while(TC--){
        input();
        solve();
    }
}