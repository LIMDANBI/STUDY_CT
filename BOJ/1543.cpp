#include<iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string doc, word;
    getline(cin, doc);
    getline(cin, word);

    int idx = 0, ans = 0;
    while(idx+word.size() <= doc.size()){
        if(doc.substr(idx, word.size()) == word) {
            ans++;
            idx+=word.size();
        }
        else idx++;
    }
    cout << ans;
}