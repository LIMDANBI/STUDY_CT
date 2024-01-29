#include<iostream>
#include<deque>
using namespace std;

int N, K;
string str;
deque<char> s;

void input(){
    cin >> N >> K;
    cin >> str;
}

void solve(){ // 숫자 K개를 지워서 얻을 수 있는 가장 큰 수
    for(char c : str){
        while(!s.empty() && s.back()<c && K){
            s.pop_back();
            K--;
        }
        s.push_back(c);
    }
    while(K--) s.pop_back();
}

void output(){
    for(char c : s) cout << c;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}