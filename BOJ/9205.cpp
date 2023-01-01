#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define MAX 101
using namespace std;

int N;
bool visited[MAX];
int sx, sy, fx, fy;
vector<pair<int, int>> pos;

void input(){
    cin >> N;
    cin >> sx >> sy;
    
    int x, y;
    pos.clear(); // init
    for(int i=0; i<N; i++){
        cin >> x >> y;
        pos.push_back({x, y});
    }
    cin >> fx >> fy;
}

void solution(){
    memset(visited, false, sizeof(visited)); // init
    queue<pair<int, int> > q;
    q.push({sx, sy});

    bool isfind = false;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if(abs(fx-x)+abs(fy-y) <= 1000){
            isfind = true;
            break;
        }
        for(int i=0; i<N; i++){
            if(visited[i]) continue; // 이미 방문한 편의점인 경우 
            if(abs(pos[i].first-x)+abs(pos[i].second-y) > 1000) continue; // 중간에 맥주가 바닥나는 경우
            q.push({pos[i].first, pos[i].second});
            visited[i] = true;
        }
    }
    isfind ? cout << "happy\n" : cout << "sad\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--){
        input();
        solution();
    }
}