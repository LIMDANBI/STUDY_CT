#include<iostream>
#include<queue>
#define MAX 1000001
using namespace std;

int F, S, G, U, D;
bool visited[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> F >> S >> G >> U >> D;
    
    visited[S] = true;
    queue<pair<int, int>> q;
    q.push({S, 0});

    int ans = MAX;
    while(!q.empty()){
        int floor = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if(floor == G) ans = cnt; // 눌러야 하는 버튼의 수의 최솟값
        else{
            if(floor+U <= F){ // 범위를 벗어나지 않는 경우 
                if(!visited[floor+U]){ // 이전에 방문하지 않은 경우
                    visited[floor+U] = true;
                    q.push({floor+U, cnt+1});
                }
            }
            if(floor-D > 0){  // 범위를 벗어나지 않는 경우 
                if(!visited[floor-D]){ // 이전에 방문하지 않은 경우
                    visited[floor-D] = true;
                    q.push({floor-D, cnt+1});
                }
            }
        }
    }

    if(ans == MAX) cout << "use the stairs";
    else cout << ans;
}