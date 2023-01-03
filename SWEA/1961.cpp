#include<iostream>
#include<string>
#define MAX 8
using namespace std;

int N;
int arr[MAX][MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> arr[i][j];
    }
}

void solution(){
    string res_90 = "";
    string res_180 = "";
    string res_270 = "";

    for(int j=0; j<N; j++){  // 90'
        for(int i=N-1; i>=0; i--) res_90+=to_string(arr[i][j]);
    }

    for(int i=N-1; i>=0; i--){ // 180'
        for(int j=N-1; j>=0; j--) res_180+=to_string(arr[i][j]);
    }

    for(int j=N-1; j>=0; j--){ // 270'
        for(int i=0; i<N; i++) res_270+=to_string(arr[i][j]);
    }

    for(int i=0; i<N*N; i+=N){
        cout << res_90.substr(i, N) << " ";
        cout << res_180.substr(i, N) << " ";
        cout << res_270.substr(i, N) << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        cout << "#" << t << "\n";
        input();
        solution();
    }
}