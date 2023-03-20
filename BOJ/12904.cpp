#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string S, T;
    cin >> S >> T;

    while (S.size() != T.size())
    {
        if (T[T.size() - 1] == 'A') // 문자열 뒤에 추가된 A 제거
            T = T.substr(0, T.size() - 1);
        else
        {
            T = T.substr(0, T.size() - 1);
            reverse(T.begin(), T.end());
        }
    }
    S == T ? cout << 1 : cout << 0; // S를 T로 바꿀 수 있으면 1을 없으면 0을 출력
}