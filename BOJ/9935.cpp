#include<iostream>
#include<deque>
using namespace std;

deque<char> dq;
int bombstrSize;
string str, bombstr;

void input(){
    cin >> str >> bombstr;
    bombstrSize = bombstr.size();
}

void solve(){
    deque<char> tmp;
    for (int i = 0; i < str.size(); i++){
        dq.push_front(str[i]);
        if(bombstrSize <= dq.size() && dq.front() == bombstr[bombstrSize-1]){
            bool ismatch = true;
            for (int j = bombstrSize - 1; j >= 0; j--){
                if(dq.front() == bombstr[j]){
                    tmp.push_front(dq.front());
                    dq.pop_front();
                }
                else{
                    ismatch = false;
                    while (!tmp.empty()){
                        dq.push_front(tmp.front());
                        tmp.pop_front();
                    }
                    break;
                }
            }
            while(ismatch && !tmp.empty()) tmp.pop_front();
        }
    }
}

void output(){
    string res = "";
    while (!dq.empty()){
        res += dq.back();
        dq.pop_back();
    }
    res == "" ? cout << "FRULA" : cout << res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}