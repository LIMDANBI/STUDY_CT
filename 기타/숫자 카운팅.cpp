#include<iostream>
#define MAX 200001
using namespace std;

int N;
int arr[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
}

int upperBound(int data){
    int upper = -1;
    int low = 0, mid, high = N - 1;
    while(low<=high){
        mid = (low + high) / 2;
        if (arr[mid] <= data){
            low = mid + 1;
            if(arr[mid] == data) upper = mid;
        }
        else high = mid - 1;
    }
    return upper;
}

int lowerBound(int data){
    int lower = -1;
    int low = 0, mid, high = N - 1;
    while(low<=high){
        mid = (low + high) / 2;
        if (arr[mid] < data) low = mid + 1;
        else{
            high = mid - 1;
            if(arr[mid] == data) lower = mid;
        }
    }
    return lower;
}

void solve(){
    int M; cin >> M;
    while(M--){
        int data; cin >> data;
        int upper = upperBound(data);
        int lower = lowerBound(data);
        if(upper!=-1) cout << upper - lower + 1 << " ";
        else cout << "0 ";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}