#include<iostream>
#include<vector>
#define MAX 101
using namespace std;

int N;
bool map[MAX][MAX];
int dy[] = {0, -1, 0, 1}; // → ↑ ← ↓
int dx[] = {1, 0, -1, 0};

void solution(int x, int y, int d, int g){

    vector<int> dir;

    // 0 세대 드래콘 커브
    map[y][x] = true;
    y+=dy[d]; x+=dx[d];
    map[y][x] = true;
    dir.push_back(d);

    while(g--){ // g세대 드래곤 커브를 만듦
        for(int i=(int)dir.size()-1; i>=0; i--){ // 거꾸로
            int nd = (dir[i]+1)%4;
            y+=dy[nd]; x+=dx[nd];
            map[y][x] = true;
            dir.push_back(nd);
        }
    }
}

void output(){ // 크기가 1×1인 정사각형의 네 꼭짓점이 모두 드래곤 커브의 일부인 것의 개수를 출력
    int ans = 0;
    for(int i=0; i<MAX-1; i++){
        for(int j=0; j<MAX-1; j++){
            if(map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1]) ans++;
        }
    } cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    int  x, y, d, g; // 드래곤 커브의 시작 점, 방향, 세대
    while(N--){
        cin >> x >> y >> d >> g;
        solution(x, y, d, g); // 드래곤 커브를 만듦
    } output();
}