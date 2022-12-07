#include<iostream>
#include<algorithm>
#include<queue>
#define MAX 25
using namespace std;

int N;
string arr[MAX];
bool visited[MAX][MAX];

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> arr[i];
}

int bfs(int i, int j){
    queue<pair<int, int>> q;
    visited[i][j] = true;
    q.push({i,j});

    int res = 1;
    while (!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int d=0; d<4; d++){
            int ny = y+dy[d];
            int nx = x+dx[d];
            if(ny<0 || ny>=N || nx<0 || nx>=N) continue;
            if(visited[ny][nx] || arr[ny][nx]!='1') continue;
            visited[ny][nx] = true;
            q.push({ny,nx});
            res++;
        }
    }
    return res;
}

void solution(){
    vector<int> ans;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(arr[i][j]=='1' && !visited[i][j]) ans.push_back(bfs(i, j));
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i=0; i<ans.size(); i++) cout << ans[i] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}