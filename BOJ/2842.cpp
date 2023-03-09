#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<set>
#define MAX 51
#define INF 1000001
using namespace std;

int N;
int py, px;
int home_cnt=0;
set<int> setAltitude;
vector<int> vecAltitude;

char town[MAX][MAX];
bool visited[MAX][MAX];
int altitude[MAX][MAX];
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void input(){
	cin >> N;

	string line;
	for(int i=0; i<N; i++){
		cin >> line;
		for(int j=0; j<N; j++) {
			town[i][j] = line[j];
			if(town[i][j] == 'P') {py=i; px=j;}
			else if(town[i][j] == 'K') home_cnt++;
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> altitude[i][j];
			setAltitude.insert(altitude[i][j]);
		}
	}

	for(auto iter : setAltitude) vecAltitude.push_back(iter);
	sort(vecAltitude.begin(), vecAltitude.end());
}

int dfs(int y, int x, int low, int high){
	visited[y][x] = true;
	int cnt = 0;
	for(int d=0; d<8; d++){
		int ny = y+dy[d];
		int nx = x+dx[d];
		if(ny<0 || ny>=N || nx<0 || nx>=N || visited[ny][nx]) continue; // 범위를 벗어난 경우, 이미 방문한 경우
		if(altitude[ny][nx]<low || altitude[ny][nx]>high) continue; // 범위 내 고도에서 방문 불가한 경우
		if(town[ny][nx] == 'K') cnt++;
		cnt+=dfs(ny, nx, low, high);
	}
	return cnt;
}

void solution(){ // 가장 작은 피로도
	int l=0, r=0, ans=INF;
	while (r < vecAltitude.size()) {
		int low = vecAltitude[l], high=vecAltitude[r];
		if(altitude[py][px]<low || altitude[py][px]>high) { r++; continue;}
		memset(visited, false, sizeof(visited));
		if(dfs(py, px, low, high)==home_cnt){
			ans = min(ans, high-low);
			l++;
		}
		else r++;
	}
	cout << ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solution();
}