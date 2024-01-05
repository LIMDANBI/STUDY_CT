#include<iostream>
#include<deque>
using namespace std;

deque<char> s, tmp;
string str, bombstr;

void input(){
    cin >> str >> bombstr;
}

void solve(){
    for (int i = 0; i < str.size(); i++){
        s.push_back(str[i]);
        if(bombstr.size() <= s.size()){ // 폭발 문자열의 길이 요건 충족
            bool ismatch = true;
            for (int j = bombstr.size() - 1; j >= 0; j--){ // 가장 최신 bombstr.size()개를 비교하여 폭발 문자열인지 확인
                if(s.back() == bombstr[j]){
                    tmp.push_back(s.back()); // 폭발 문자열이 아닌 경우, 다시 메인 스택에 저장해주기위해 임시 저장
                    s.pop_back();
                }
                else{ // 폭발 문자열과 match되지 않는 경우
                    ismatch = false;
                    while (!tmp.empty()){ // 임시 스택에 저장해둔 폭발 문자열이 아닌 문자열을 다시 메인 스택에 옮겨줌
                        s.push_back(tmp.back());
                        tmp.pop_back();
                    }
                    break; // 더 이상 볼 필요 없음
                }
            }
            while (ismatch && !tmp.empty()) tmp.pop_back();  // 폭발 문자열을 저장해둔 임시 stack을 비워줌
        }
    }
}

void output(){
    string res = "";
    while (!s.empty()){
        res += s.front();
        s.pop_front();
    }
    res == "" ? cout << "FRULA" : cout << res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}