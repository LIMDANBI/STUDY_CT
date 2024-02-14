#include<iostream>
#include<vector>
#define MAX 1030
#define SIZE 10
using namespace std;

int K;
int N;
int order[MAX];
vector<int> tree[SIZE];

void input(){
    cin >> K;
    N = (1<<K)-1;
    for (int i=0; i<N; i++)
        cin >> order[i];
}

void recur(int s, int e, int d){
    if(s >= e) return;
    int n = (s+e)/2;
    tree[d].push_back(order[n]);
    recur(s, n, d+1);
    recur(n+1, e, d+1);
}

void output(){
    for (int i=0; i<K; i++){
        for(int node : tree[i])
            cout << node << " ";
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    recur(0, N, 0);
    output();
}