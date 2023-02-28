#include<iostream>
using namespace std;

void swap(char *a, char *b){
    char *tmp = a;
    a = b;
    b = tmp;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--){
        string str; cin >> str;

        int top = str.size()-1;
        while(top>0 && str[top]<=str[top-1]) top--;

        if(top == 0) cout << "BIGGEST\n";
        else{
            int target = str.size()-1;
            while(target>0 && str[target]<=str[top-1]) target--;

            swap(str[top-1], str[target]);
            
            int k = str.size()-1;
            while(top < k) swap(str[top++], str[k--]);
            cout << str << "\n";
        }
    }
}