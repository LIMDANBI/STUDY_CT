#include<iostream>
#include<deque>
using namespace std;

deque<char> s1, s2;
string str, bombstr;

void input(){
    cin >> str >> bombstr;
}

void solve(){
    for (int i = 0; i < str.size(); i++){
        s1.push_back(str[i]);
        if(bombstr.size() <= s1.size()){
            bool ismatch = true;
            for (int j = bombstr.size() - 1; j >= 0; j--){
                if(s1.back() == bombstr[j]){
                    s2.push_back(s1.back());
                    s1.pop_back();
                }
                else{
                    ismatch = false;
                    while (!s2.empty()){
                        s1.push_back(s2.back());
                        s2.pop_back();
                    }
                    break;
                }
            }
            while (ismatch && !s2.empty()) s2.pop_back();
        }
    }
}

void output(){
    string res = "";
    while (!s1.empty()){
        res += s1.front();
        s1.pop_front();
    }
    res == "" ? cout << "FRULA" : cout << res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}