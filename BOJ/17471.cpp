#include<iostream>
#include<vector>
#define MAX 11
#define INF 100001
using namespace std;

int N;
int ans = INF;
int total = 0; // 총 인구 수
int people[MAX]; // 구역의 인구 수 
bool visited[MAX]; // 방문 여부 저장
int isgroup1[MAX]; // 그룹 1에 속하는지
vector<int> v[MAX]; // 각 구역과 인접한 구역의 정보

void input() {
	cin >> N; 
	for (int i = 0; i < N; i++) {
		cin >> people[i];
		total += people[i];
	}
	
	int num, next;
	for (int now = 0; now < N; now++) {
		cin >> num;
		while (num--){
			cin >> next; next--;
			v[now].push_back(next);
			v[next].push_back(now); // 양방향
		}
	}
}

int check(int node, bool isg1) { // 인접 구역 check
	int res = 1;
	visited[node] = true;
	for (auto next : v[node]) {
		if (visited[next] || isgroup1[next] != isg1) continue; // 이미 방문한 경우, 같은 그룹이 아닌 경우
		res += check(next, isg1);
	} 
	return res;
}

void solution(int cnt, int people1, int size1) { 
	if (cnt == N) {
		if (size1 == 0 || size1==N) return; // 두 선거구로 나누지 못한 경우
		
		int g1, g2;
		for (int i = 0; i < N; i++) {
			isgroup1[i] ? g1 = i : g2 = i; // 시작 정점 찾기
			visited[i] = false; // 그룹 연결 여부 체크를 위한 초기화
		}

		int people2 = total - people1;
		int res1 = check(g1, true), res2 = check(g2, false);
		if (res1 == size1 && res2 == N - size1) ans = min(ans, abs(people1-people2));
		return; 
	}

	isgroup1[cnt] = true;
	solution(cnt + 1, people1+ people[cnt], size1 + 1);

	isgroup1[cnt] = false;
	solution(cnt + 1, people1, size1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution(0, 0, 0);
	ans == INF ? cout << -1 : cout << ans; // 두 선거구의 인구 차이의 최솟값 출력 (나눌 수 없는 경우에는 -1 출력)
}