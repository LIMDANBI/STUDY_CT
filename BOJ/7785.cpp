#include<iostream>
#include<map>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;

    string name, state;
    map<string, int> m;
    while (N--){
        cin >> name >> state;
        if(state == "enter") m[name] = 1;
        else if(state == "leave") m.erase(name);
    }

    for (auto iter = m.rbegin(); iter != m.rend(); ++iter){
        cout << iter->first << "\n";
    }
}