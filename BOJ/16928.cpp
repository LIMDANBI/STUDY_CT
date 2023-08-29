#include<iostream>
#include<queue>
#define MAX 101
using namespace std;

int N, M;
int path[MAX];
bool visited[MAX];

void input(){
    cin >> N >> M;

    int x, y;
    while (N--){
        cin >> x >> y;
        path[x] = y;
    }
    while(M--){
        cin >> x >> y;
        path[x] = y;
    }
}

int solution(){
    queue<pair<int, int>> q;
    q.push({1, 0});

    while (!q.empty()){
        int num = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (num == 100) return cnt;
        for (int i = 1; i<=6; i++){
            if(visited[num+i]) continue;
            visited[num+i] = true;
            if(path[num+i]!=0) q.push({path[num+i], cnt+1});
            else q.push({num+i, cnt+1});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    cout << solution();
}