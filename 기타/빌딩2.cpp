#include <iostream>
#include <stack>
using namespace std;
#define MAXN 100005

int N; //빌딩수
int H[MAXN]; //빌딩높이
int sol[MAXN]; //각 빌딩에서 보이는 빌딩 번호

void input() {
	cin >> N;
	for (int i=1; i<=N; i++) cin >> H[i];
}

void solution(){
    stack<int> st; // idx
    for (int idx = 1; idx <= N; idx++){
        while (!st.empty() && H[st.top()] < H[idx]){
            sol[st.top()] = idx;
            st.pop();
        }
        st.push(idx);
    }
}

void output() {
	for (int i=1; i<=N; i++) cout << sol[i] << "\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
    output();
}