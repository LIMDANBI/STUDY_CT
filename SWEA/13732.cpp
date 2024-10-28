#include<iostream>
#define MAX 25
using namespace std;

int N;
char map[MAX][MAX];
bool visited[MAX][MAX];

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            visited[i][j] = false;
        }
    }
}

bool solution()
{
    int si = 0, sj = 0, cnt = 0;

    // 1. 정사각형 시작점 찾기
    bool iscContinue = true;
    for (int i = 0; i < N && iscContinue; i++){
        for (int j = 0; j < N && iscContinue; j++){
            if(map[i][j] == '#'){
                si = i;
                sj = j;
                while (j < N && map[i][j++]=='#')
                    cnt++;
                iscContinue = false;
            }
        }
    }

    // 2. 정사각형 칠하기
    for (int i = si; i < si + cnt; i++){
        for (int j = sj; j < sj + cnt; j++){
            if(i>=N || j>=N || map[i][j]!='#')
                return false;
            visited[i][j] = true;
        }
    }

    // 3. 이외에 # 있는지 확인하기
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(map[i][j] == '#' && !visited[i][j])
                return false;
        }
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int t = 1; t <= T; t++)
    {
        input();
        cout << "#" << t << " " << (solution() ? "yes\n" : "no\n");
    }
}