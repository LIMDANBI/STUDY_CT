#include<iostream>
#define MAX 100001
#define INF 1000000001 // 10000 * 100000
using namespace std;

int video[MAX];
int N, M, ans = 0; 
int low = 0, high = INF;

void input() {
	cin >> N >> M;
	for(int i = 0; i < N; i++) cin >> video[i];
}

bool check(int size) { //  블루레이 제한 크기
    int s = 0, cnt = 0; // 현재 크기, 블루레이 개수
    for(int i=0; i<N; i++){
        if(size < video[i]) return false; // 담을 수 없음
        if(size < s+video[i]){
            cnt++;
            s = video[i];
        }
        else s+=video[i];
    }
    if (s > 0) cnt += 1;
    if (cnt <= M) return true;
    return false;
}

void solution() { // 가능한 블루레이 크기중 최소를 출력 (매개변수 탐색)
	while (low <= high) {
		int mid = (low + high) / 2;
		if (check(mid)) high = mid - 1; // 블루레이의 크기를 더 낮춰도 됨
		else low = mid + 1; // 블루레이의 크기를 더 늘려야 함
	} cout << low;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}