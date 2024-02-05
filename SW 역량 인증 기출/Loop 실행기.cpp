#include<iostream>
#include<string>
using namespace std;

string loop;

void input(){
    cin >> loop;
}

int print_loop(int idx){ // Loop문 작업 실행 순서 출력
    int start;
    int cnt = loop[idx+1]-'0';
    while (cnt--){ // 반복 횟수
        start = idx+2; 
        while (loop[start] != '>'){
            if(loop[start] == '<'){ // 중첩 loop인 경우
                start = print_loop(start);
            }
            else cout << loop[start];
            start++;
        }
    }
    return start;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    print_loop(0);
}