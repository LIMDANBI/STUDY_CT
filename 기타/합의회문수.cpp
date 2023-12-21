#include<iostream>
using namespace std;

int reverse(int num){ // 1 ≦ num ≦ 1,000,000
    int res = 0;
    while(num){
        res = res*10 + num%10;
        num/=10;
    }
    return res;
}

void solve(int num){
    int sum = num + reverse(num);
    if(sum == reverse(sum)) cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N;
    while(N--){
        cin >> M;
        solve(M);
    }
}