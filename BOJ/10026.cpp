#include<iostream>
#include<cstring>
#define MAX 101
using namespace std;

int N;
int no, yes;
char arr[MAX][MAX];
bool visited[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        string line; cin >> line;
        for(int j=0; j<N; j++) arr[i][j] = line[j];
    }
}

void no_solution(int y, int x){
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue;
        if(arr[y][x] != arr[ny][nx]) continue;
        no_solution(ny, nx);
    }
}

void yes_solution(int y, int x){
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y+dy[d];
        int nx = x+dx[d];
        if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue;
        if(arr[y][x] != arr[ny][nx] && (arr[y][x]=='B' || arr[ny][nx] =='B')) continue;
        yes_solution(ny, nx);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();

    // 적록색약 x
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visited[i][j]) continue;
            no_solution(i, j);
            no++;
        }
    }

    // init
    memset(visited, false, sizeof(visited));

    // 적록색약
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visited[i][j]) continue;
            yes_solution(i, j);
            yes++;
        }
    }
    cout << no << " " << yes;
}