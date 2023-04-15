#include <iostream>
#define MAX 1000000
using namespace std;

int N, B, C;
int arr[MAX];

void input(){
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	cin >> B >> C;
}

void solution(){
	long long ans = N;
	for (int i = 0; i < N; i++){
		arr[i] -= B;
		if(arr[i] > 0){
			ans += (arr[i] / C);
			if(arr[i]%C)
				ans++;
		}
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}