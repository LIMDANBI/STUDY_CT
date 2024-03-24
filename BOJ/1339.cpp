#include<iostream>
#include<algorithm>
#define MAX 26
using namespace std;

int N;
int alpha[MAX];
string word[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> word[i];
}

void solve(){

    for (auto w : word){
        int pow = 1;
        for (int i = w.size()-1; i >= 0; i--){
            alpha[w[i]-'A'] += pow;
            pow *= 10;
        }
    }
    sort(alpha, alpha + MAX);

    int ans = 0;
    int curNum = 9;
    for (int i = MAX - 1; i >= 0; i--){
        if(!alpha[i]) break;
        ans += (alpha[i] * curNum);
        curNum--;
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}