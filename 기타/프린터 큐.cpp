#include <iostream>
#include <queue>
using namespace std;
#define MAXN 105

int N, M; //문서수, 궁금한 문서 번호
int P[MAXN]; //문서 우선순위
int priocnt[10];

queue<int> q; // idx 

void init(){
    for(int i=1; i<10; i++) priocnt[i] = 0;
    while(!q.empty()) q.pop();
}

void input() {
    cin >> N >> M;
    for (int i=0; i<N; i++) {
        q.push(i);
        cin >> P[i];
        priocnt[P[i]]++;
    }
}

int solve(){
    int ans=1;
    for(int prio=9; prio>0; prio--){ // 현재 보고 있는 우선 순위
        while(priocnt[prio]){
            if(P[q.front()] == prio){
                if(q.front() == M) return ans;
                priocnt[prio]--; ans++;
            }
            else q.push(q.front());
            q.pop();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t=1; t<=T; t++){
        init();
        input();
        cout << solve() << "\n";
    }
}