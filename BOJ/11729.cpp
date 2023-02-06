#include<iostream>
using namespace std;

int ans = 0;

void hanoi(int n, int from, int mid, int to){
    if(n == 0) return; // 더 이상 옮길 게 없는 경우
    hanoi(n-1, from, to, mid);
    cout << from << " " << to << "\n";
    hanoi(n-1, mid, from, to);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    cout << (1<<N)-1 << "\n";
    hanoi(N, 1, 2, 3);
}