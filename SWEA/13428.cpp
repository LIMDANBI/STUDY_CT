#include<iostream>
#define MAX 10
using namespace std;

string N;
int minVal, maxVal;

void input(){
    cin >> N;
    minVal = maxVal = stoi(N);
}

void solution(){
    for (int i = 0; i < N.size()-1; i++){
        for (int j = i + 1; j < N.size(); j++){
            string strN = N;
            strN[i] = N[j];
            strN[j] = N[i];
            if(strN[0]=='0') continue;

            int intN = stoi(strN);
            minVal = min(minVal, intN);
            maxVal = max(maxVal, intN);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++){
        input();
        solution();
        cout << "#" << t << " " << minVal << " " << maxVal << "\n";
    }
}