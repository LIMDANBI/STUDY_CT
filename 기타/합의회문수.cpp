#include<iostream>
#include<string>
using namespace std;

string solve(int M){
    
    string str = to_string(M), reverse="";
    for(int i = str.size()-1; i>=0; i--) reverse += str[i];

    int sum = M + stoi(reverse);
    str = to_string(sum);
    for(int i=0; i<str.size()/2; i++){
        if(str[i]!=str[str.size()-1-i]) return "NO";
    }
    return "YES";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N;
    while(N--){
        cin >> M;
        cout << solve(M) << "\n";
    }
}