#include<iostream>
#include<vector>
using namespace std;

void solution(){
    string line; cin >> line;
    vector<char> v1, v2;

    char tmp;
    for(int i=0; i<line.size(); i++){
        if(line[i] == '<'){
            if(v1.size()==0) continue;
            tmp = v1[v1.size()-1];
            v1.pop_back();
            v2.push_back(tmp);
        }
        else if(line[i] == '>'){
            if(v2.size()==0) continue;
            tmp = v2[v2.size()-1];
            v2.pop_back();
            v1.push_back(tmp);
        }
        else if(line[i] == '-'){
            if(v1.size()==0) continue;
            v1.pop_back();
        }
        else v1.push_back(line[i]);
    }

    for(int i=0; i<v1.size(); i++) cout << v1[i];
    for(int i=v2.size()-1; i>=0; i--) cout << v2[i];
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--) solution();
}