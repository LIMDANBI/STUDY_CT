#include<iostream>
#include<stack>
using namespace std;

string str;

void input(){
    cin >> str;
}

void solve() { // 균형 잡힌 문자열이 될 수 있도록 뒤집어야 하는 괄호 문자의 최소 수
    stack<char> s;

    int ans=0, size=(int)str.size();
    for (int idx=0; idx<size; idx++) {
        char c = str[idx];
        if(c == '('){
            if(size-idx <= s.size()){ // 남은 것들이 모두 ')'이어야 하는 경우
                ans++; s.pop();
            }
            else s.push('(');
        }
        else{
            if(s.empty()){ // '('가 필요한 경우
                ans++; s.push('(');
            }
            else s.pop();
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}