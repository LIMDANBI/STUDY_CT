#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
 
string str;
 
void input(){
    cin >> str;
}
 
int solve(){
    int lev=0, open=0, close=0;
    for(char c : str){
        if(c == '('){
            lev++;
            open++;
        }
        else{
            lev--;
            close++;
        }
        if(lev == 1) open = 0;
        if(lev < 0) return close;
    }
    return open;
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}