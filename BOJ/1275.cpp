#include<iostream>
#include<vector>
using namespace std;

int N, Q;
int treeIdx = 1;
vector<long long> tree;

void make_tree(){
    for (int i = treeIdx - 1; i > 0; i--)
        tree[i] = tree[i << 1] + tree[(i << 1) | 1];
}

long long sum(int left, int right){
    left += (treeIdx - 1);
    right += (treeIdx - 1);

    long long res = 0;
    while(left<=right){
        if((left&1)==1) res+=tree[left];
        if((right&1)==0) res+=tree[right];
        left = (left + 1) >> 1;
        right = (right - 1) >> 1;
    }
    return res;
}

void update(int idx, long long val){
    idx += (treeIdx - 1);
    tree[idx] = val;
    while((idx>>=1)>0) tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;

    while(treeIdx < N) treeIdx <<= 1;
    tree.resize(treeIdx << 1);
    for (int i = treeIdx; i < treeIdx + N; i++) cin >> tree[i];

    make_tree();

    int x, y, a;
    long long b;
    while (Q--){
        cin >> x >> y >> a >> b;
        if(x < y) cout << sum(x, y) << "\n";
        else cout << sum(y, x) << "\n";
        update(a, b);
    }
}