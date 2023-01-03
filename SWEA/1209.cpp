#include<iostream>
#define MAX 100
using namespace std;

int arr[MAX][MAX];

void input(){
    int n; cin >> n;
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++) cin >> arr[i][j];
    }
}

int solution(){
    int ans = 0;

    // row
    for(int i=0; i<MAX; i++){
        int sum = 0;
        for(int j=0; j<MAX; j++) sum+=arr[i][j];
        ans = max(ans, sum);
    }

    // col
    for(int j=0; j<MAX; j++){
        int sum = 0;
        for(int i=0; i<MAX; i++) sum+=arr[i][j];
        ans = max(ans, sum);
    }

    // diagonal
    int sum1 = 0, sum2 = 0;
    for(int i=0; i<MAX; i++) {
        sum1+=arr[i][i];
        sum2+=arr[i][MAX-i];
    }
    ans = max(ans, max(sum1, sum2));

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    for(int t=1; t<=10; t++){
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}