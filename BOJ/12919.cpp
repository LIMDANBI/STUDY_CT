#include<iostream>
using namespace std;

int ans = 0;
string S, T;

void abGame(string str){
    if(str.size() <= S.size()){
        if(str == S) ans = 1;
        return ;
    }
    if(str[str.size()-1] == 'A') abGame(str.substr(0, str.size()-1));
    if(str[0] == 'B'){
        string tmp = "";
        for(int i=str.size()-1; i>0; i--) tmp+=str[i];
        abGame(tmp);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S >> T;
    abGame(T);
    cout << ans;
}