#include<iostream>
#include<cstring>
#include<queue>
#define MAX 16
using namespace std;
 
int arr[MAX][MAX];
int sy, sx, ey, ex;
bool visited[MAX][MAX];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
 
void input() {
    int n; cin >> n;
 
    for (int i = 0; i < MAX; i++) {
        string str; cin >> str;
        for (int j = 0; j < MAX; j++) {
            arr[i][j] = str[j] - '0';
            if (arr[i][j] == 2) { // 출발점
                sy = i;
                sx = j;
            }
            else if (arr[i][j] == 3) { // 도착점
                ey = i;
                ex = j;
            }
        }
    }
}
 
int solution() {
    memset(visited, false, sizeof(visited)); // init
    queue<pair<int, int>> q;
    visited[sy][sx] = true;
    q.push({ sy, sx }); // 시작점
 
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
 
        if (y == ey && x == ex) return 1; // 도착가능
 
        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX) continue; // 범위를 벗어나는 경우
            if (visited[ny][nx] || arr[ny][nx] == 1) continue; // 이미 방문한 경우, 벽인 경우
            visited[ny][nx] = true;
            q.push({ ny, nx });
        }
    }
    return 0; // 도착 불가능
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int t = 1; t <= 10; t++) {
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}