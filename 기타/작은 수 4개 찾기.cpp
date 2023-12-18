#include <iostream>
using namespace std;
#define MAXN 300001

int N;
int A[MAXN];

void input(){
	cin >> N;
	for (int i=0; i<N; i++) cin >> A[i];
}

void solve(){
    for (int i = 0; i < 4; i++){
        for (int j = i + 1; j < N; j++){
            if(A[i] > A[j]){
                int tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
}

void output(){
	for (int i=0; i<4; i++) cout << A[i] << " ";
	cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
    solve();
    output();
}