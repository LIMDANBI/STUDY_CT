#include<iostream>
#include<string>
#include<vector>
#define MAX 51
using namespace std;

int N;
string S;
vector<int> v[MAX];

void input(){
    cin >> N;
    cin >> S;
}

void solve(){
    int lev = 0;
    int idx = 0;
    int size = (int)S.size();

    while(idx < size){
        if(S[idx] == '<'){
            lev++;
            idx++;
        }
        else if(S[idx] == '>'){
            lev--;
            idx++;
        }
        else{ // 스파이 이름
            int s = idx;
            while(S[idx]!='<' && S[idx]!='>') idx++;
            string name = S.substr(s, idx-s);
            v[lev].push_back(stoi(name));
        }
    }
}

void output(){
    for(int n : v[N]) cout << n << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}