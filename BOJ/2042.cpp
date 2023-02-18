#include<iostream>
#include<vector>
using namespace std;

int N, M, K, tree_size = 1;
vector<long long> tree; //index start with 1

void make_indexed_tree() {
	for (int i = tree_size - 1; i > 0; i--) {
		tree[i] = tree[i << 1] + tree[(i << 1) | 1]; // left node(*2) + right node(*2+1)
	}
}

void update(int idx, long long val) {
	idx += (tree_size - 1); // tree에 알맞는 index로 변환
	tree[idx] = val; // b번째 값을 c로 update
	while ((idx >>= 1) > 0) tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1]; // 조상들도 update
}

long long interval_sum(int left, int right) {
	left += (tree_size - 1); right += (tree_size - 1); // tree에 알맞는 index로 변환

	long long res = 0;
	while (left <= right) {
		if ((left & 1) == 1) res += tree[left]; // tree의 right일 때 값을 취함
		if ((right & 1) == 0) res += tree[right]; // tree의 left일 때 값을 취함
		left = (left + 1) >> 1; // (left+1)/2 node로 이동
		right = (right - 1) >> 1; // (right-1)/2 node로 이동
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;

	// set tree size
	while (tree_size < N) tree_size <<= 1;
	tree.resize(tree_size << 1);

	// set leaf node
	long long tmp;
	for (int i = tree_size; i < tree_size + N; i++) {
		cin >> tmp; tree[i] = tmp;
	}

	make_indexed_tree();

	long long a, b, c;
	for (int i = 0; i < M + K; i++) { // query
		cin >> a >> b >> c;
		if (a == 1) update(b, c); // b번째 값을 c로 바꿈
		else if (a == 2) cout << interval_sum(b, c) << "\n"; // [b, c] 구간 합 출력
	}
}