#include<iostream>
using namespace std;

char vowel[5] = {'a', 'e', 'i', 'o', 'u'};

bool check_pwd(string pwd){
    
    int cntV=0, cntC=0;
    bool isVowel=false;
    for(int i=0; i<pwd.size(); i++){

        // 1. 모음(a,e,i,o,u) 하나를 반드시 포함
        bool isConsonant = true;
        for(int j=0; j<5; j++){
            if(pwd[i] == vowel[j]) {
                isVowel = true;
                isConsonant = false;
            }
        }

        // 2. 모음이 3개 혹은 자음이 3개 연속으로 오면 안 됨
        if(isConsonant) {
            cntC++;
            if(cntC >= 3) return false;
            cntV = 0;
        }
        else{
            cntV++;
            if(cntV >= 3) return false;
            cntC = 0;
        }

        // 3. 같은 글자가 연속적으로 두번 오면 안되나, ee 와 oo는 허용
        if(i!=0 && pwd[i-1] == pwd[i] && pwd[i]!='e' && pwd[i]!='o') return false;
    }
    if(isVowel) return true; return false;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    while(1){
        string pwd; cin >> pwd;
        if(pwd == "end") break;
        if(check_pwd(pwd)) cout << "<" << pwd << "> is acceptable.\n";
        else cout << "<" << pwd << "> is not acceptable.\n";
    }
}