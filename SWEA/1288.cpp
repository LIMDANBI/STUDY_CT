#include<iostream>
#include<cstring>
using namespace std;

bool issaw[10];

long long solution(){
    long long N; cin >> N;

    int n = 0, saw = 0;
    memset(issaw, false, sizeof(issaw));
    while(++n){
        long long num = N * n;
        string str = to_string(num);
        for (int i = 0; i < str.size(); i++){
            if(issaw[str[i]-'0']) continue;
            issaw[str[i]-'0'] = true;
            if(++saw == 10) return num;
        }
    }
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        cout << "#" << t << " " << solution() << "\n";
    }
}