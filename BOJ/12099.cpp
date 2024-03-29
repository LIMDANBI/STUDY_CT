#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN 100005
#define MAXQ 5005
using namespace std;

struct MENU {
    int spicy, sweet;
    bool operator < (const MENU &m) const{
        return spicy < m.spicy;
    }
};
struct SECTION {int u, v, x, y;};

int N, Q;
MENU menu[MAXN];
vector<SECTION> section;

void input(){
    cin >> N >> Q;

    int a, b;
    for (int i = 0; i < N; i++){
        cin >> a >> b;
        menu[i] = (MENU){a, b};
    }

    int u, v, x, y;
    for (int i = 0; i < Q; i++){
        cin >> u >> v >> x >> y;
        section.push_back((SECTION){u, v, x, y});
    }
}

int lower_bound(int val){ // val 이상의 값이 처음으로 등장하는 위치
    int lower = 0;
    int low = 0, mid, high = N - 1;
    while (low <= high){
        mid = (low + high) / 2;
        if (menu[mid].spicy >= val){
            lower = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return lower;
}

int upper_bound(int val){ // val 초과의 값이 처음으로 등장하는 위치
    int upper = N;
    int low = 0, mid, high = N - 1;
    while (low <= high){
        mid = (low + high) / 2;
        if (menu[mid].spicy > val){
            upper = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    return upper;
}

void solve(){

    // 1. 정렬
    sort(menu, menu + N);

    // 2. 매개변수 탐색
    for (auto s : section) {
        int ans = 0;
        int lower = lower_bound(s.u);
        int upper = upper_bound(s.v);

        for (int i = lower; i < upper; i++){
            if(s.x <= menu[i].sweet && menu[i].sweet <= s.y)
                ans++;
        }
        cout << ans << "\n";
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}