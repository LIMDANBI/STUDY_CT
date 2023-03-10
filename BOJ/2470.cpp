#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;
vector<int> v;

void input() {
	cin >> N;

	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp; 
		v.push_back(tmp);
	}
}

void solution() {
	sort(v.begin(), v.end()); // 정렬

	int a=v[0], b=v[N-1];// 정답이 될 두 용액
	int l = 0, r = N-1; // two pointer
	int min_val = 2000000001;

	while(l<=r){
		int tmp = v[l]+v[r];
		if(abs(tmp) < min_val && l!=r){
			min_val = abs(tmp);
			a=v[l]; b=v[r];
			if(min_val == 0) break;
		}
		if(tmp < 0) l++;
		else r--;
	}
	cout << a << " " << b;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}