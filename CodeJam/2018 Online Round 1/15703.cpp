#include<iostream>
#include<queue>
#define MAX 1001
using namespace std;

int N;
int dice[MAX];

void input(){
    cin >> N;
    for (int i = 0, n; i < N; i++) {
        cin >> n;
        dice[n]++;
    }
}

void solve(){
    int ans = 0;
    while (N){ // 남은 주사위가 있는 동안 반복
        int h = 0; // 주사위 탑의 높이
        for (int n = 0; n < MAX; n++){ // 제일 위에는 젝일 작은 수가 오는 것이 유리
            if(dice[n] == 0) continue; // 주사위가 없는 경우
            while (1){
                dice[n]--; N--; h++;
                if(n+1 < h){ // 해당 숫자로 더 이상 탑을 쌓을 수 없는 경우
                    dice[n]++; N++; h--;
                    break;
                }
                if(dice[n] == 0) break;
            }
        }
        ans++;
    }
    cout << ans; // 만들 수 있는 주사위 탑의 최소 개수
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}
