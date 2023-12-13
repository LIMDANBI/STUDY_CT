#include<iostream>
using namespace std;

int R;

void input(){
    cin >> R;
}

void solution(){
    int cnt = 0;
    for(int y=1; y<R; y++){
        for(int x=1; x<R; x++){
            if(y*y+x*x <= R*R) cnt++;
        }
    }
    cout << cnt*4;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}