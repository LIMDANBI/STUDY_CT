#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
vector<pair<int, pair<int, int> > > fraction;

void input(){
    cin >> N;
}

void solution(){
    for(int parent=2; parent<=N; parent++){ // 분모
        for(int child=1; child<parent; child++){ // 분자
            fraction.push_back({child*100000/parent, {child, parent}});
        }
    }
    sort(fraction.begin(), fraction.end());
}

void output(){
    cout << "0/1\n";
    for(int i=0; i<fraction.size(); i++){
        if(i!=0 && fraction[i].first == fraction[i-1].first) continue;
        cout << fraction[i].second.first << "/" << fraction[i].second.second << "\n";
    }
    cout << "1/1\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}