#include<iostream>
#include<string>
#include<stack>
#define MAX 32001
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	string expr; cin >> expr;
	stack<char> st;

	// 연산자 우선 순위 : () > *, / > +, -
	for (int i = 0; i < expr.size(); i++) {
		if (expr[i] == '+' || expr[i] == '-') {
			while (!st.empty() && st.top()!='(') {
				cout << st.top(); st.pop();
			}
			st.push(expr[i]);
		}
		else if (expr[i] == '*' || expr[i] == '/') {
			while (!st.empty() && (st.top() == '*' || st.top() == '/')) {
				cout << st.top(); st.pop();
			}
			st.push(expr[i]);
		}
		else if (expr[i] == '(') st.push(expr[i]);
		else if (expr[i] == ')') {
			while (st.top() != '(') {
				cout << st.top();
				st.pop();
			} st.pop(); // '(' pop
		}
		else cout << expr[i]; // 알파벳 대문자
	}
	while (!st.empty()) { // 남은 연산자 출력
		cout << st.top(); st.pop();
	}
}