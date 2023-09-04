#include<iostream>
#define MAX 100001
using namespace std;

int N, M;
int pos[MAX];

void input(){
    cin >> N >> M;
    for (int i = 0; i < M; i++)
        cin >> pos[i];
}

bool ispossible(int h){
    if(pos[0]-h>0 || pos[M-1]+h<N) return false; // 처음과 끝 확인
    for (int i = 0; i < M; i++){ // 중간 확인
        if(pos[i]+h < pos[i+1]-h) return false;
    }
    return true;
}

void solution(){
    int low = 1, mid, high = N;
    while (low<=high){
        mid = (low + high) / 2;
        if(ispossible(mid)) high=mid-1;
        else low = mid+1;
    }
    cout << low;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}