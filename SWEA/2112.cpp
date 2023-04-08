#include <iostream>
#define MAX_Y 14
#define MAX_X 21
using namespace std;

int Y, X, K;
int ans = 0;
bool film[MAX_Y][MAX_X];

void input(){
    cin >> Y >> X >> K;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++)
            cin >> film[i][j];
    }
    ans = K; // init
}

bool check() { // 단면의 모든 세로방향에 대해서
    // 동일한 특성의 셀들이 K개 이상 연속적으로 있는 경우에만 성능검사를 통과
    for (int x = 0; x < X; x++) {
        int tmp = 1;
        bool before = film[0][x];
        for (int y = 1; y < Y; y++) {
            if (film[y][x] == before) {
                if (++tmp >= K)
                    break;
            }
            else {
                before = film[y][x];
                tmp = 1;
            }
        }
        if (tmp < K) // 성능 검사를 통과할 수 없는 경우
            return false;
    } return true;
}

void solution(int cnt, int use) {
    if (cnt == Y || ans <= use) { // 모두 시도해본 경우, 이미 더 작은 해답을 찾은 경우

        if (check()) // 성능 검사를 통과한 경우
            ans = min(ans, use);
        return;
    }
    // as it is
    solution(cnt + 1, use);

    // save state
    int tmp[MAX_X];
    for (int x = 0; x < X; x++)
        tmp[x] = film[cnt][x];

    // change all A
    for (int x = 0; x < X; x++)
        film[cnt][x] = false; // A
    solution(cnt + 1, use + 1);

    // change all B
    for (int x = 0; x < X; x++)
        film[cnt][x] = true; // B
    solution(cnt + 1, use + 1);

    // recovery state
    for (int x = 0; x < X; x++)
        film[cnt][x] = tmp[x];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++){
        input();
        solution(0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
}