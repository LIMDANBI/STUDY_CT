#include<iostream>
#include<algorithm>
#define MAX 2001
using namespace std;

int N;
int num[MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> num[i];
}

void solution(){
    sort(num, num+N);
    
    int ans = 0;
    for(int i=0; i<N; i++){
        int val = num[i];
        int l=0, r=N-1, sum;
        while(l < r){
            sum = num[l]+num[r];
            if(sum == val){
                if(l!=i && r!=i){
                    ans++;
                    break;
                }
                else if(l==i) l++;
                else if(r==i) r--;
            }
            else if(sum < val) l++;
            else r--;
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}