#include <iostream>
#include <deque>
using namespace std;

int N;

void input(){
	cin >> N;
}

void solve(){
    deque<int> dq;
    for(int num=1; num<=N; num++) dq.push_back(num);
    while (dq.size()){
        int repeat = dq.back()/2;
        while (repeat--){
            int num = dq.front();
            dq.pop_front();
            dq.push_back(num);
        }
        cout << dq.front() << " "; // 카드를 넘김
        dq.pop_front();
    }
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
    solve();
}