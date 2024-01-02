#include<iostream>
#define MAX 7
using namespace std;

int N, M;
int seq[MAX];
bool visited[MAX];

void input(){
    cin >> N >> M;
}

void duplicatePermutation(int cnt){
    if(cnt == N){
        for(int i=0; i<N; i++) cout << seq[i] << " ";
        cout << "\n";
        return ;
    }
    for(int num=1; num<=6; num++){
        seq[cnt] = num;
        duplicatePermutation(cnt+1);
    }
}

void duplicateCombination(int idx, int cnt){
    if(cnt == N){
        for(int i=0; i<N; i++) cout << seq[i] << " ";
        cout << "\n";
        return ;
    }
    for(int num=idx; num<=6; num++){
        seq[cnt] = num;
        duplicateCombination(num, cnt+1);
    }
}

void permutation(int cnt){
    if(cnt == N){
        for(int i=0; i<N; i++) cout << seq[i] << " ";
        cout << "\n";
        return ;
    }
    for(int num=1; num<=6; num++){
        if(visited[num]) continue;
        visited[num] = true;
        seq[cnt] = num;
        permutation(cnt+1);
        visited[num] = false;
    }
}

void solve(){
    if(M==1) duplicatePermutation(0);
    else if(M==2) duplicateCombination(1, 0);
    else if(M==3) permutation(0);
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}