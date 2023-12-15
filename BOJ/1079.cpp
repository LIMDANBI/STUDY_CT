#include<iostream>
using namespace std;

string str;

void input(){
    cin >> str;
}

void solution(){
    int ans=0, siz=0;
    for(int i=0; i<str.size(); i++){
        if(str[i] == '(') siz++;
        else { // str[i] == ')'
            siz--;
            if(str[i-1] =='(') ans+=siz;
            else ans++;
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}