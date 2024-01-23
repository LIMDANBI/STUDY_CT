#include <iostream>
#include <algorithm>
#define MAXC 20005
#define MAXV 15
using namespace std;

int sol; // 정답
int N; // 실행 코드의 데이터 개수
int M; // 바이러스의 데이터 개수
int code[MAXC]; // 실행 코드의 데이터
int virus[MAXV]; // 바이러스의 데이터


void input(void) {
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> code[i];
	for (int i = 0; i < M; i++) cin >> virus[i];
}

int find(int start) {
	int tmp[MAXV]; // 부분 코드
	for (int i = 0; i < M; i++) tmp[i] = code[start+i];
    sort(tmp, tmp+M); // 쉬운 비교를 위해 코드를 정렬

    int isvirus = 1;
    int diff = virus[0] - tmp[0];
	for (int i = 0; i < M; i++){ // 정렬된 부분 코드 비교 (차이가 같은 경우 바이러스)
        if(virus[i]-tmp[i] != diff) isvirus = false;   
    }
	return isvirus;
}

void solve(void) {
    sort(virus, virus+M); // 쉬운 비교를 위해 바이러스 정렬
	for (int i = 0; i <= N - M; i++) sol += find(i);
	cout << sol;
}

int main(void) {
	input();
	solve();
}
