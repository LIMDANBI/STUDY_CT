#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T, N, M, num; cin >>T;
    while(T--){
        unordered_map<int, int> note;

        cin >> N;
        while(N--){
            cin >> num;
            note[num] = 1;
        }

        cin >> M;
        while(M--){
            cin >> num;
            note[num] == 1 ? cout << "1\n" : cout << "0\n";
        }
    }
}