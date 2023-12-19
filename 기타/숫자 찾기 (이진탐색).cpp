#include<iostream>
#define MAX 50005
using namespace std;

int N;
int num[MAX];

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> num[i];
}

int binarySearch(int data){
    int low = 1, mid, high = N;
    while(low<=high){
        mid = (low + high) / 2;
        if(num[mid] == data) return mid;
        else if(num[mid] < data) low = mid+1;
        else high = mid-1;
    }
    return 0;
}

void solve(){
    int T; cin >> T;
    while (T--){
        int data; cin >> data;
        cout << binarySearch(data) << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}