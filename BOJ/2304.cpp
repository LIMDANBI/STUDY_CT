#include<iostream>
#include<algorithm>
#define MAX 1001
using namespace std;

int N, L, H;
int pillars[MAX];
int maxVal, maxIdx;

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> L >> H;
        pillars[L] = H;
        if(maxVal < pillars[L]){
            maxIdx = L;
            maxVal = H;
        }
    }
}

void solution(){
    int ans=maxVal, h = 0;

    // left
    for (int i = 1; i < maxIdx; i++){
        h = max(h, pillars[i]);
        ans += h;
    }

    // right
    h = 0;
    for (int i = MAX - 1; i > maxIdx; i--){
        h = max(h, pillars[i]);
        ans += h;
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}