#include<iostream>
#define MAX 41
using namespace std;

int zero[MAX], one[MAX];

void solution(){
    zero[0] = 1;
    one[1] = 1;
    for(int i=2; i<MAX; i++){
        zero[i] = zero[i-2]+zero[i-1];
        one[i] = one[i-2]+one[i-1];
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solution();
    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        cout << zero[n] << " " << one[n] << "\n";
    }
}