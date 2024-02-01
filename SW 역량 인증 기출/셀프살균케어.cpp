#include<iostream>
#include<vector>
using namespace std;

struct POS{int y, x;};
vector<POS> pos;

int N; // 필터 한 변의 크기
int L; // LED의 범위(길이) 
int M; // 살균대상의 개수

void input(){
    cin >> N >> M >> L;
    pos.resize(M);
    for(int i=0; i<M; i++) cin >> pos[i].y >> pos[i].x;
}

int counnt(int sy, int sx, int ey, int ex){
    int cnt = 0;
    for(auto p : pos){
        if((sy<=p.y&&p.y<=ey) && (sx<=p.x&&p.x<=ex)) cnt++;
    }
    return cnt;
}

void solve(){ // 한번에 살균할 수 있는 최대 개수
    int ans = 0;
    int half = L/2;
    for(int h=1; h<half; h++){
        int w = half-h;
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}