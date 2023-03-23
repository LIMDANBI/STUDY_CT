#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N, B;
    cin >> N >> B;

    vector<int> v;
    while (N / B)
    {
        v.push_back(N % B);
        N /= B;
    }
    if (N != 0)
        v.push_back(N);

    for (int i = v.size() - 1; i >= 0; i--)
        v[i] < 10 ? cout << v[i] : cout << (char)(v[i] + 'A' - 10);
}