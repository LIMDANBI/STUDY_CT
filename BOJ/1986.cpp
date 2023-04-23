#include<iostream>
#include<vector>
#define MAX 1001
using namespace std;

int N, M;
bool isHurdle[MAX][MAX];
bool danger[MAX][MAX];
int Kdy[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int Kdx[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int Qdy[] = {0, 0, -1, 1, -1, -1, 1, 1};
int Qdx[] = {-1, 1, 0, 0, -1, 1, -1, 1};

void Knight(int y, int x){
    danger[y][x] = true;
    for (int d = 0; d < 8; d++){
        int ny = y + Kdy[d];
        int nx = x + Kdx[d];
        if(ny<1 || ny>N || nx<1 || nx>M) continue;
        danger[ny][nx] = true;
    }
}

void Queen(int y, int x){
    danger[y][x] = true;
    for (int d = 0; d < 8; d++){
        for(int k=1; ; k++){
            int ny = y + Qdy[d]*k;
            int nx = x + Qdx[d]*k;
            if(ny<1 || ny>N || nx<1 || nx>M || isHurdle[ny][nx]) break;
            danger[ny][nx] = true;
        }
    }
}

void solution(){
    cin >> N >> M;

    int k, q, p, y, x;

    // Queen
    cin >> q;
    vector<pair<int, int> > v;
    while (q--){
        cin >> y >> x;
        v.push_back(make_pair(y, x));
    }

    // Knight
    cin >> k;
    while(k--){
        cin >> y >> x;
        isHurdle[y][x] = true;
        Knight(y, x);
    }

    // Pawn
    cin >> p;
    while(p--){
        cin >> y >> x;
        isHurdle[y][x] = true;
        danger[y][x] = true;
    }

    for (int i = 0; i < (int)v.size(); i++)
        Queen(v[i].first, v[i].second);
}

void output(){
    int ans = 0;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            if(!danger[i][j]) ans++;
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solution();
    output();
}