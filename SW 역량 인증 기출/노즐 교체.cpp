#include<iostream>
#define MAX 1001
using namespace std;

int N;
int map[MAX][MAX];

void init(){}

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void solve(){

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    solve();
}