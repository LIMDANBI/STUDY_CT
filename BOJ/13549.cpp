#include<iostream>
#include<queue>
#define MAX 100001
using namespace std;

int N, K;
int visit_time[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    
    int ans = MAX;// 수빈이가 동생을 찾을 수 있는 가장 빠른 시간
    for(int i=0; i<MAX; i++) visit_time[i] = MAX;
    
    queue<pair<int, int>> q;
    visit_time[N] = 0;
    q.push({N, 0});

    while(!q.empty()){
        int pos = q.front().first;
        int sec = q.front().second;
        q.pop();

        if(pos == K) ans = min(ans, sec);
        else{
            if(pos*2 < MAX && visit_time[pos*2] > sec){
                visit_time[pos*2] = sec;
                q.push({pos*2, sec});
            }
            
            if(pos+1 <= K && visit_time[pos+1] > sec+1){
                visit_time[pos+1] = sec+1;
                q.push({pos+1, sec+1});
            }

            if(pos-1 >= 0 && visit_time[pos-1] > sec+1){
                visit_time[pos-1] = sec+1;
                q.push({pos-1, sec+1});
            }
        }
    }
    cout << ans;
}