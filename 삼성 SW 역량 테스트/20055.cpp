#include<iostream>
#define MAX 202
using namespace std;

int N, K;
int A[MAX];
bool robot[MAX];

void input(){
    cin >> N >> K;
    for (int i = 0; i < 2 * N; i++)
        cin >> A[i];
}

void rotate(){ // 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전

    int tmpA = A[0];
    bool tmpR = robot[0];
    A[0] = A[2 * N - 1];
    robot[0] = robot[2 * N - 1];

    for (int i = 2 * N - 1; i > N; i--){
        A[i] = A[i - 1];
        robot[i] = robot[i - 1];
    }

    A[N] = A[N - 1];
    robot[N] = robot[N - 1];
    for (int i = N - 1; i > 1; i--){
        A[i] = A[i - 1];
        robot[i] = robot[i - 1];
    }
    A[1] = tmpA;
    robot[1] = tmpR;
    robot[N - 1] = false; // 내리는 위치
}

void move(){
    for (int i = N - 1; i > 0; i--){ // 가장 먼저 벨트에 올라간 로봇부터
        if(robot[i-1] && !robot[i] && A[i]){ // 이동하려는 칸에 로봇이 없고, 내구도가 남아있는 경우
            robot[i] = robot[i - 1];
            robot[i - 1] = false;
            A[i]--;
        }
    }
    robot[N - 1] = false; // 내리는 위치
}

void put(){
    if(A[0]>0){
        A[0]--;
        robot[0] = true;
    }
}

bool check(){
    int res = 0;
    for (int i = 0; i < 2 * N; i++){
        if(A[i] == 0)
            res++;
    }
    return res >= K; // 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료
}

void solution(){
    int ans = 0;
    while (++ans) {
        rotate();
        move();
        put();
        if (check())
            break;
    }
    cout << ans;
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}