#include<iostream>
#define BOMB 210
#define MAX 8
using namespace std;

int K; // 처음 폭탄을 가진 사람의 번호
int N; // 게임이 진행되는 동안 공개된 퀴즈의 수
int T; // 퀴즈를 풀거나 통과를 결정할 때까지 걸린 시간
char Z; // 정답 여부

void solve(){ // 폭탄이 터질 때 폭탄을 갖고 있던 사람의 번호를 출력
    cin >> K >> N;

    int k=K, t=0; // 현재 폭탄을 가지고 있는 사람 번호, 진행된 시간
    for(int i=0; i<N; i++){
        cin >> T >> Z;
        if((t+=T) > BOMB) break; // 문제를 풀다 시간이 끝난 경우
        if(Z == 'T'){ // 다음 사람에게 문제를 넘김
            if(++k > MAX) k = 1;
        }
    }
    cout << k;
}

int main (){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}