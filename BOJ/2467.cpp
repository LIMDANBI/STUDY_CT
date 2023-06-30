#include<iostream>
#include<algorithm>
#define MAX 100001
using namespace std;

int arr[MAX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    // input
    int N; cin >> N;
    for(int i=0; i<N; i++) cin >> arr[i];

    sort(arr, arr+N); // sort for two pointer

    //variable declaration
    int ans=2000000001, absSum;
    int l=0, r=N-1, left, right;

    while(1){
        if(l>=r) break; // end condition

        absSum = abs(arr[l]+arr[r]);
        if(absSum < ans) { // ans update
            left = arr[l];
            right = arr[r];
            ans = absSum;
        }
        
        arr[l]+arr[r] <= 0 ? l++ : r--; // two pointer
    }

    cout << left << " " << right; // output
}