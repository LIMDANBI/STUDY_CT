#include<iostream>
#define MAX 1001
using namespace std;

int N;
int map[MAX][MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void solve(){
    int row=0, col=0;
    
    // 1. 행 기준으로 열 선택
    for(int y=0; y<N; y++){
        int sum[2]={0, 0};
        for(int x=0; x<N; x++){
            sum[x%2]+=map[y][x];
        }
        col += max(sum[0], sum[1]);
    }

    // 2. 열 기준으로 행 선택
    for(int x=0; x<N; x++){
        int sum[2]={0, 0};
        for(int y=0; y<N; y++){
            sum[y%2]+=map[y][x];
        }
        row += max(sum[0], sum[1]);
    }

    // 3. 교체되는 노즐들의 오염도 최대합
    cout << max(row, col);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}