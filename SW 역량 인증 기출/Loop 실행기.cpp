#include<iostream>
#include<string>
using namespace std;

void print_loop(string loop){ // Loop문 작업 실행 순서 출력

    int cnt = loop[1] - '0'; // 반복 횟수
    int size = (int)loop.size();
    
    for (int c = 0; c < cnt; c++){
        int idx = 2;
        string str = "";
        while(idx < size){
            if(loop[idx] == '<'){ // 중첩 loop가 시작되는 경우
                // 이전까지 출력 처리
                cout << str;
                str = "";

                // 중첩 loop
                int len = 0;
                while(loop[idx + len] != '>') len++;
                print_loop(loop.substr(idx, len));
                idx += len;
            }
            else if(loop[idx]!='>') str += loop[idx];
            idx++;
        }
        cout << str;
    }
}

void solve() {

    // 1. 입력
    string loop;
    cin >> loop;

    // 2. Loop문 작업 실행 순서 출력
    print_loop(loop);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}