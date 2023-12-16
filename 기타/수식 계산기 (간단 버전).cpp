#include <iostream>
#include <stack>
using namespace std;
#define MAX (20)

int N;
int M[MAX + 10];
char op[MAX + 10];

void input(){
	cin >> N;
	cin >> M[0];
	for(int i=1; i<N; i++){
		cin >> op[i] >> M[i];
	}
}

void solution(){
    stack<int> num_st;
    num_st.push(M[0]);

    for (int i = 1; i < N; i++){
        if(op[i] == '+') num_st.push(M[i]);
        else if(op[i] == '-') num_st.push(-M[i]);
        else if(op[i] == '*'){
            int tmp = num_st.top();
            num_st.pop();
            num_st.push(tmp * M[i]);
        }
        else if(op[i] == '/'){
            int tmp = num_st.top();
            num_st.pop();
            num_st.push(tmp / M[i]);
        }
    }

    int ans = 0;
    while(!num_st.empty()){
        ans += num_st.top();
        num_st.pop();
    }
    cout << ans; // ans
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}
