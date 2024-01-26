#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
 
string str;
 
void input(){
    cin >> str;
}

int isBalance(){
    int st = 0; // '(' 개수 저장
    for(char c : str){
        if(c == '(') st++;
        else st--;
    }
    return st;
}

int getCnt(int dir){ // 전체 문자열이 균형 잡히게 되는 위치의 수 구하기
    int ans = 0, st = 0;
    if(dir < 0){
        for(char c : str){
            if(c == '(') st++;
            else{
                ans++;
                if(--st<0) break;
            }
        }
    }
    else{
        reverse(str.begin(), str.end()); // 뒤에서부터 보기위해
        for(char c : str){
            if(c == ')') st++;
            else{
                ans++;
                if(--st<0) break;
            }
        }
    }
    return ans;
}
 
int solve(){
    int res = isBalance();
    if(res == 0) cout << 0; 
    else cout << getCnt(res);
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}