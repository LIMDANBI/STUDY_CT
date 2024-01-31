#include<iostream>
#include<string>
#include<queue>
#define MAX 10000
#define SIZE 4
using namespace std;

struct DATA{int num, cnt;};

int start, dest;
bool notPrime[MAX], visited[MAX];

void input(){
    cin >> start >> dest;
}

void eratosthenes(){
    for(int i=2; i*i<=MAX; i++){
        for(int j=i*2; j<MAX; j+=i) notPrime[j] = true;
    }
}

int bfs(){
    queue<DATA> q;
    q.push({start, 0});
    visited[start] = true;

    while(!q.empty()){
        int num = q.front().num;
        int cnt = q.front().cnt;
        q.pop();
        
        if(num == dest) return cnt;
        for(int idx=0; idx<SIZE; idx++){
            int inum;
            string snum = to_string(num); // 정수 -> 문자열
            for(int n=0; n<10; n++){
                if(idx==0 && n==0) continue; // 0으로 시작 x                
                snum[idx] = n + '0'; // 변경
                inum = stoi(snum); // 문자열 -> 정수
                if(visited[inum] || notPrime[inum]) continue; // 이미 방문했거나, 소수가 아닌경우
                q.push({inum, cnt+1});
                visited[inum] = true;
            }
        }
    }
    return -1; // 디버깅
}

void solve(){

    // 1. 에라토스테네스의 체
    eratosthenes();

    // 2. BFS
    cout << bfs();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}