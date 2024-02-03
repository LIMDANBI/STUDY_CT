#include<iostream>
#include<vector>
using namespace std;

int N; // 필터 한 변의 크기
int L; // LED의 범위(길이) 
int M; // 살균대상의 개수
int y[110]; // 살균대상의 y 좌표 배열
int x[110]; // 살균대상의 x 좌표 배열

void input(){
    cin >> N >> L >> M;
    for (int i = 0; i < M; i++)
        cin >> y[i] >> x[i];
}

int counnt(int sy, int sx, int ey, int ex){
    int cnt = 0;
    for (int i = 0; i < M; i++){
        if((sy<=y[i]&&y[i]<=ey) && (sx<=x[i]&&x[i]<=ex)) cnt++;
    }
    return cnt;
}

void solve(){ // 한번에 살균할 수 있는 최대 개수
    int ans = 0;
    int half = L/2;
    for (int h = 1; h < half; h++){
        int w = half-h;
        for (int i = 0; i < M; i++){
            for (int j = 0; j < M; j++){
                ans = max(ans, counnt(y[i], x[j], y[i]+h, x[j]+w));
            }
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}