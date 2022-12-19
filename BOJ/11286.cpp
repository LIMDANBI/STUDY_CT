#include<iostream>
#include<queue>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    priority_queue<int> positive, negative;

    int N; cin >> N;
    while(N--){
        int x; cin >> x;
        if(x > 0) positive.push(-x);
        else if(x < 0) negative.push(x);
        else if(x == 0){ // 절댓값이 가장 작은 값을 출력하고 그 값을 제거
            if(positive.empty() && negative.empty()) cout << 0 << "\n";
            else if(positive.empty()){
                cout << negative.top() << "\n";
                negative.pop();
            }
            else if(negative.empty()){
                cout << -positive.top() << "\n";
                positive.pop();
            }
            else{
                if(positive.top() <= negative.top()){
                    cout << negative.top() << "\n";
                    negative.pop();
                }
                else{
                    cout << -positive.top() << "\n";
                    positive.pop();
                }
            }
        }
    }
}