#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, B;
    cin >> N >> B;

    if (N == 0)
        cout << 0;
    else
    {
        vector<int> v;
        while (N)
        {
            v.push_back(N % B);
            N /= B;
        }
        for (int i = v.size() - 1; i >= 0; i--)
            v[i] < 10 ? cout << v[i] : cout << (char)(v[i] + 'A' - 10);
    }
}