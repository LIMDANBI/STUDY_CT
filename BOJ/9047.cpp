#include <iostream>
#include <algorithm>
#define SIZE 4
using namespace std;

int TC, N;

int kaprekar(int num){
    int arr[SIZE];

    for (int i = 0; i < SIZE; i++){
        arr[i] = num % 10;
        num /= 10;
    }
    sort(arr, arr + SIZE);
    return (arr[3]*1000 + arr[2]*100 + arr[1]*10 + arr[0]) - (arr[0]*1000 + arr[1]*100 + arr[2]*10 + arr[3]);
}

int main(){
    cin >> TC;
    while(TC--){
        cin >> N;

        int ans=0, num = N;
        while (num != 6174){
            num = kaprekar(num);
            ans++;
        }

        cout << ans << "\n";
    }
}