#include<iostream>
#include<stack>
#define MAX 80001
using namespace std;

int N;
int H[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> H[i];
}

void solve(){
    long long ans = 0;

    stack<int> st;
    for(int i=0; i<N; i++){
        while(!st.empty() && st.top() <= H[i]) st.pop();
        ans += st.size();
        st.push(H[i]);
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}