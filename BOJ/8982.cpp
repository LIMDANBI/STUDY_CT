#include<iostream>
#define MAX 5001
using namespace std;

int N, K, A;
int drain[MAX], water[MAX]; // 빠져나간 물의 양, 초기 물의 양

void input(){
    cin >> N;

    int x, y; cin >> x >> y;

    int r = 0;
    for (int i = 0; i < N - 2; i++){
        cin >> x >> y;
        if(i%2 != 0){
            while(r < x) water[r++] = y; // 초기 물의 양
        }
    }
    cin >> x >> y; A = x;
}

void solution(){
    cin >> K;

    int a, b, c, b2;
    while (K--) { // 물이 빠져나감 
        cin >> a >> b >> c >> b2;
        
        drain[a] = water[a]; // 모두 빠져나감

        int l = a, h = water[l];
        while(--l >= 0){ // 좌
            h = min(h, water[l]);
            drain[l] = max(drain[l], h);
        }

        int r = a; h = water[r]; 
        while(++r < A){ // 우
            h = min(h, water[r]);
            drain[r] = max(drain[r], h);
        }
    }
}

void output(){
    int ans = 0;
    for (int i = 0; i < A; i++) ans+=(water[i] - drain[i]);
    cout << ans;
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}