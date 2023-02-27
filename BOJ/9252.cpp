#include<iostream>
#include<string>
#define MAX 1001
using namespace std;

int LCS[MAX][MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    string s1, s2; cin >> s1 >> s2;
    int l1=s1.size(), l2=s2.size();

    for(int i=1; i<=l1; i++){
        for(int j=1; j<=l2; j++){
            if(s1[i-1]==s2[j-1]) LCS[i][j] = LCS[i-1][j-1]+1;
            else LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]);
        }
    }

    string lcs = "";
    int lcsLen = LCS[l1][l2];
    while(lcs.size()!=lcsLen){
        if(LCS[l1][l2] == LCS[l1-1][l2-1]) {l1--; l2--;}
        else if(LCS[l1][l2] == LCS[l1-1][l2]) l1--;
        else if(LCS[l1][l2] == LCS[l1][l2-1]) l2--;
        else{
            lcs+=s1[l1-1]; 
            l1--; l2--;
        }
    }

    cout << lcsLen << "\n";
    for(int i=lcs.size()-1; i>=0; i--) cout << lcs[i];
}