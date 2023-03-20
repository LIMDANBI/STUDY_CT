#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#define MAX 27
using namespace std;

string expr;
int N, num[MAX];

void input()
{
    cin >> N;
    cin >> expr;
    for (int i = 0; i < N; i++)
        cin >> num[i];
}

void solution()
{
    stack<double> s;

    double ans = 0;
    for (int i = 0; i < expr.size(); i++)
    {
        if ('A' <= expr[i] && expr[i] <= 'Z')
            s.push(num[expr[i] - 'A']);
        else
        {
            double a = s.top();
            s.pop();
            double b = s.top();
            s.pop();

            if (expr[i] == '+')
                s.push(b + a);
            else if (expr[i] == '-')
                s.push(b - a);
            else if (expr[i] == '*')
                s.push(b * a);
            else if (expr[i] == '/')
                s.push(b / a);
        }
    }
    cout << fixed << setprecision(2) << s.top();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}