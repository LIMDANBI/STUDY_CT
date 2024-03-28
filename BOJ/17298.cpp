#include<iostream>
#include<stack>
#define MAX 1000005
using namespace std;

struct INFO{int num, idx;};

int N;
int A[MAX];
int ans[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
}

void solve(){
    stack<INFO> st;
    for (int i = 0; i < N; i++){
        while(!st.empty() && st.top().num < A[i]){
            INFO tmp = st.top(); st.pop();
            ans[tmp.idx] = A[i];
        }
        st.push((INFO){A[i], i});
    }
    while (!st.empty()){
        INFO tmp = st.top(); st.pop();
        ans[tmp.idx] = -1;
    }
}

void output(){
    for (int i = 0; i < N; i++)
        cout << ans[i] << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}