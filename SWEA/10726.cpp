#include<iostream>
#include<bitset>
using namespace std;

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T, N, M; cin >> T;
    for (int t = 1; t <= T; t++){
        cin >> N >> M;
        int mask = (1 << N) - 1;
        string ans = ((M & mask) == mask) ? "ON" : "OFF";
        cout << "#" << t << " " << ans << "\n";
    }
}