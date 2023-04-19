#include<iostream>
#define MAX 1000001
using namespace std;

int N, M;
int root[MAX];

int find_(int a){
    if(root[a] == a) return a;
    return root[a] = find_(root[a]);
}

void union_(int a, int b){
    root[find_(b)] = find_(a);
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) root[i] = i;

    int oper, a, b;
    while(M--){
        cin >> oper >> a >> b;
        if(oper == 0) union_(a, b);
        else {
            if(find_(a) == find_(b)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}