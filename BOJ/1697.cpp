#include<iostream>
#include<queue>
#define MAX 100001
using namespace std;

int N, K;
bool visited[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    
    int ans = MAX;// 수빈이가 동생을 찾을 수 있는 가장 빠른 시간
    
    queue<pair<int, int>> q;
    visited[N] = true;
    q.push({N, 0});

    while(!q.empty()){
        int pos = q.front().first;
        int sec = q.front().second;
        q.pop();

        if(pos == K) ans = min(ans, sec);
        else{
            if(pos+1 < MAX && !visited[pos+1]){
                visited[pos+1] = true;
                q.push({pos+1, sec+1});
            }

            if(pos-1 >= 0 && !visited[pos-1]){
                visited[pos-1] = true;
                q.push({pos-1, sec+1});
            }

            if(pos*2 < MAX && !visited[pos*2]){
                visited[pos*2] = true;
                q.push({pos*2, sec+1});
            }
        }
    }
    cout << ans;
}