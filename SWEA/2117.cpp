#include <iostream>
#define MAX 21
using namespace std;

int N, M, ans;
bool map[MAX][MAX];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) cin >> map[i][j];
    }
}

void solution() {
    for (int k = 1; k <= N + 1; k++){

        int cost = k * k + (k - 1) * (k - 1);

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++){

                // 서비스를 제공받는 집의 수
                int home = 0;

                // 영역 내 집들의 수 count
                for (int r = y - k + 1; r < y + k; r++){
                    for (int c = x - k + 1; c < x + k; c++){
                        if (r < 0 || r >= N || c < 0 || c >= N) continue; // 격자 범위를 벗어나는 경우
                        if (abs(y - r) + abs(x - c) >= k) continue; // 마름모 내에 있지 않은 경우
                        if (map[r][c]) home++;
                    }
                }

                if (home * M - cost >= 0 && home > ans) ans = home;
            }
        }
    }
}

int main() {
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++){
        ans = 0;
        input();
        solution();
        cout << "#" << t << " " << ans << "\n";
    }
}