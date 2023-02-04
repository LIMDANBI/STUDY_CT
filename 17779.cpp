#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 1000000001
#define MAX 101
using namespace std;

int ans = INF;
int N, total=0;
bool border[MAX][MAX];
int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, -1, 1};
int A[MAX][MAX], population[5];

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            total+=A[i][j];
        }
	}
}

int diff(int x, int y, int d1, int d2) {
    memset(population, 0, sizeof(population)); // 인구 수
    memset(border, false, sizeof(border)); // 경계선

    int nx = x, ny = y;
    int mvoe_cnt[] = {d2, d1, d2, d1};
    for(int d=0; d<4; d++){
        for(int i=0; i<mvoe_cnt[d]; i++){
            nx+=dx[d]; ny+=dy[d];
            border[nx][ny] = true; // 경계 설정
        }
    }

    // 좌측 상단 (1번 선거구)
    for(int r=1; r<x+d1; r++){ // 1 ≤ r < x+d1
        for(int c=1; c<=y && !border[r][c]; c++) population[0]+=A[r][c]; //  1 ≤ c ≤ y
    }

    // 우측 상단 (2번 선거구)
    for(int r=1; r<=x+d2; r++){ // 1 ≤ r ≤ x+d2
        for(int c=N; c>y && !border[r][c]; c--) population[1]+=A[r][c]; //  y < c ≤ N
    }

    // 좌측 하단 (3번 선거구)
    for(int r=x+d1; r<=N; r++){ // x+d1 ≤ r ≤ N
        for(int c=1; c<y-d1+d2 && !border[r][c]; c++) population[2]+=A[r][c]; // 1 ≤ c < y-d1+d2
    }

    // 우츨 하단 (4번 선거구)
    for(int r=x+d2+1; r<=N; r++){ // x+d2 < r ≤ N
        for(int c=N; c>=y-d1+d2 && !border[r][c]; c--) population[3]+=A[r][c]; // y-d1+d2 ≤ c ≤ N
    }

    population[4] = total;
    for(int i=0; i<4; i++) population[4]-=population[i]; // 5번 선거구
	sort(population, population+5); // 정렬
    return population[4]-population[0]; // 최대 - 최소
}

void solution() {
	for (int d1=1; d1<N; d1++) { // d1, d2 ≥ 1
		for (int d2=1; d2<N; d2++) {
			for (int x=1; x<=N-d1-d2; x++) { // 1 ≤ x < x+d1+d2 ≤ N
				for (int y=d1+1; y<=N-d2; y++) // 1 ≤ y-d1 < y < y+d2 ≤ N
					ans = min(ans, diff(x, y, d1,d2));
			}
		}
	} cout << ans;
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}