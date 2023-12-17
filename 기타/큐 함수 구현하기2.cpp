#include <iostream>
using namespace std;

#define MAXN 10005
int N; //명령개수
int cmd[MAXN];
int a[MAXN];

int wp, rp;
int que[MAXN];

void push(int d){
    que[wp++] = d;
}

void pop() {
    rp++;
}

int front() {
    return que[rp];
}

bool empty() {
    return rp==wp;
}

int size() {
    return wp-rp;
}

void solve(){
	wp = rp = 0;//초기화
	for (int i=0; i<N; i++){
		switch(cmd[i]){
		case 0: //읽고 제거
			if (empty()) {
				cout << "E" << "\n";
			}
			else{
				cout << front() << "\n";
				pop();
			}
			break;
		case 1: //저장
			push(a[i]);
			break;
		default: //2 : 저장 개수
			cout << size() << "\n";
		}
	}
}

void input(){
	cin >> N;
	for (int i=0; i<N; i++){
		cin >> cmd[i];
		if (cmd[i] == 1){
			cin >> a[i];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
}