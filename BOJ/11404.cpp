#include<iostream>
#define MAX 101
#define INF 100000001
using namespace std;

int n, m;
int cost[MAX][MAX];

void init(){
    for(int i=1; i<MAX; i++){
        for(int j=1; j<MAX; j++){
            if(i == j) continue;
            cost[i][j] = INF;
        }
    }
}

void input(){
    cin >> n >> m;

    int a, b, c;
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        cost[a][b] = min(cost[a][b], c);
    }
}

void floyd(){
    for(int k=1; k<=n; k++){
        for(int a=1; a<=n; a++){
            for(int b=1; b<=n; b++){
                cost[a][b] = min(cost[a][b], cost[a][k]+cost[k][b]);
            }
        }
    }
}

void output(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(cost[i][j] == INF) cout << 0 << " ";
            else cout << cost[i][j] << " ";
        } cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    input();
    floyd();
    output();
}