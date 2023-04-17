#include<iostream>
#include<vector>
#define MAX 7
using namespace std;

struct POS { int y, x; };
vector<POS> teacher, noting;

int N;
int studentCnt=0;
char map[MAX][MAX];
bool possible = false;
int dy[] = {-1, 1, 0, 0}; // 상 하 좌 우
int dx[] = {0, 0, -1, 1};

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if(map[i][j] == 'X') noting.push_back({i,j});
            else if(map[i][j]=='T') teacher.push_back({i,j});
            else studentCnt++;
        }
    }
}

void test(){
    for (int i = 0; i < (int)teacher.size(); i++){
        int y = teacher[i].y;
        int x = teacher[i].x;

        for (int d = 0; d < 4; d++){
            for (int k = 1;; k++){
                int ny = y + dy[d] * k;
                int nx = x + dx[d] * k;
                if(ny<0 || ny>=N || nx<0 || nx>=N || map[ny][nx] == 'O') break;
                if(map[ny][nx] == 'S') return;
            }
        }
    }
    possible = true;
}

void solution(int cnt, int idx){ // 장애물을 정확히 3개 설치하여 모든 학생들이 선생님들의 감시를 피하도록 할 수 있는지
    if(possible) return;
    if(cnt == 3){
        test();
        return;
    }
    for (int i = idx; i < (int) noting.size(); i++){
        int y = noting[i].y, x = noting[i].x;
        map[y][x] = 'O';
        solution(cnt + 1, i + 1);
        map[y][x] = 'X';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(0, 0);
    possible ? cout << "YES" : cout << "NO";
}