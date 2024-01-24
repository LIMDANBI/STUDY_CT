#include<iostream>
#include<string>
using namespace std;

void print_loop(int cnt, string loop) {

    //cout << cnt << " " << loop << " print_loop\n";
    for (int c = 0; c < cnt; c++) {
        string cumul = "";
        int idx = 0, size = loop.size();
        while (idx < size) {
            if (loop[idx] == '<') { // 1. loop가 시작하는 경우

                cout << cumul;
                cumul = "";

                int len = 1, cnt = loop[idx + 1] - '0';
                for (int i = idx + 1; i < size; i++) {
                    len++;
                    if (loop[i] == '>') break;
                }
                print_loop(cnt, loop.substr(idx + 2, len));
                idx += len;
            }
            else if (loop[idx] == '>') { // 2. loop가 끝나는 경우
                cout << cumul;
                cumul = "";
                idx++;
            }
            else cumul += loop[idx++]; // 3. 반복 출력할 문자열인 경우
        }
    }
}

void solve() { // Loop문 작업 실행 순서를 출력
    string loop; cin >> loop;
    int cnt = loop[1] - '0';
    loop = loop.substr(2);
    print_loop(cnt, loop);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}