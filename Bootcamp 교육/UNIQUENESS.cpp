#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int N;
vector<string> order; // 순서 유지를 위해
unordered_map<string, vector<int> > map;

void input() {
    cin >> N;
    for (int idx = 1; idx <= N; idx++) {
        string str; cin >> str;
        if (map.find(str) == map.end()) { // 처음 나온 문자열
            map.insert({ str, {idx} });
            order.push_back(str);
        }
        else { // 두번 이상 나온 문자열
            map[str].push_back(idx);
        }
    }
}

void solve() {
    bool unique = true;
    for (string key : order) {
        auto it = map.find(key);
        if (it->second.size() == 1) continue; // 해당 문자열이 유니크함
        unique = false; // 두번 이상 나온 문자열이 존재
        
        cout << key << " ";
        for (int idx : it->second) cout << idx << " ";
        cout << "\n";
    }
    if (unique) cout << "unique";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}