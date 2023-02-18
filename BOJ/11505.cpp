#include<iostream>
#include<vector>
#define MOD 1000000007
using namespace std;

int N, M, K, tree_size = 1;
vector<int> tree;

void make_indexed_tree(){
    for(int i=tree_size-1; i>0; i--){
        tree[i] = (tree[i<<1] * (long long)tree[i<<1|1])%MOD;
    }
}

void update(int idx, int val){
    idx += (tree_size-1);
    tree[idx] = val;
    while ((idx>>=1) > 0){ // ancestor update
        tree[idx] = (tree[idx<<1] * (long long)tree[idx<<1|1])%MOD;
    }   
}

int interval_multiplication(int left, int right){
    
    left += (tree_size-1);
    right += (tree_size-1);

    long long res = 1;
    while (left<=right) {
        if((left&1)==1) res = (res * tree[left])%MOD;
        if((right&1)==0) res = (res * tree[right])%MOD;
        left = (left+1)>>1;
        right = (right-1)>>1;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> N >> M >> K;
    
    // set tree size
    while (tree_size < N) tree_size <<= 1;
    tree.resize(tree_size << 1);

    // set leaf node
    for(int i=tree_size; i<tree_size+N; i++) cin >> tree[i];
    for(int i=tree_size+N; i<(tree_size<<1); i++) tree[i] = 1; // 곱셈을 위해

    make_indexed_tree();

    int a, b, c;
    for(int i=0; i<M+K; i++){
        cin >> a >> b >> c;
        if(a==1) update(b, c);
        else if(a==2) cout << interval_multiplication(b, c) << "\n";
    }
}