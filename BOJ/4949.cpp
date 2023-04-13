#include <iostream>
#include <stack>
using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while(true){
        string str; 
        getline(cin, str);
        
        if(str == ".") break;

        stack<char> s;
        bool isbalance = true;
        for (int i = 0; i < (int)str.size(); i++){
            if(str[i] == '[' || str[i] =='(')
                s.push(str[i]);
            else if(str[i] == ']'){
                if(s.empty() || s.top()!='[') {isbalance = false; break;}
                else s.pop();
            }
            else if(str[i] == ')'){
                if(s.empty() || s.top()!='(') {isbalance = false; break;}
                else s.pop();
            }
        }
        if(!s.empty()) isbalance = false;
        isbalance ? cout << "yes" : cout << "no"; cout << "\n";
    }
}