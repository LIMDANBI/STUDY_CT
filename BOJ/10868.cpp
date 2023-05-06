#include<algorithm>
#include<iostream>
#include<vector>
#define INF 1000000001
using namespace std;

int treeIdx=1;
vector<int> tree;

void make_indexed_tree(){
    for (int i = treeIdx - 1; i > 0; i--)
        tree[i] = min(tree[i << 1], tree[(i << 1) | 1]);
}

long long get_min_val(int left, int right){
    left += (treeIdx - 1);
    right += (treeIdx - 1);

    int res = INF;
    while (left <= right) {
        if((left&1)==1) res = min(res, tree[left]); // right면 비교
        if((right&1)==0) res = min(res, tree[right]); // left면 비교
        left = (left + 1) >> 1;
        right = (right - 1) >> 1;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, M;
    cin >> N >> M;

    while(treeIdx < N) treeIdx <<= 1;
    tree.resize(treeIdx << 1);
    for(int i=1; i<tree.size(); i++) tree[i] = INF; // init
    for (int i = treeIdx; i < treeIdx + N; i++) cin >> tree[i];

    make_indexed_tree();

    int a, b;
    for (int i = 0; i < M; i++){
        cin >> a >> b;
        cout << get_min_val(a, b) << "\n";
    }
}