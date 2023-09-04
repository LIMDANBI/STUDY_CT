#include<iostream>
#include<vector>
#define MAX 51
using namespace std;

int N;
int W[MAX], H[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> W[i] >> H[i];
}

void solution(){
    for (int i = 0; i < N; i++){
        int rank = 1;
        for (int j = 0; j < N; j++){
            if(i == j) continue;
            if(W[i]<W[j] && H[i]<H[j]) rank++;
        }
        cout << rank << " ";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}