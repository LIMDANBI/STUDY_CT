#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#define SIZE 4
using namespace std;

int main(){
    int TC; cin >> TC;
    while(TC--){
        string N; cin >> N;
        int ans = 0, maxVal, minVal, diff = stoi(N);
        
        while (diff != 6174){
            vector<char> v;
            string minStr="", maxStr="";

            for(char c : N) v.push_back(c);
            sort(v.begin(), v.end());
            for(int i=0; i<SIZE; i++){
                minStr = minStr + v[i];
                maxStr = maxStr + v[SIZE-i-1];
            }
            minVal = stoi(minStr);
            maxVal = stoi(maxStr);
            diff = maxVal - minVal;
            N = to_string(diff);
            while(N.size() < SIZE) N = "0" + N;
            
            ans++;
        }
        cout << ans << "\n";
    }
}