#include<iostream>
using namespace std;

int N, R, C, ans=0;

void solution(int r, int c, int size) {
    if(r==R && c==C){
        cout << ans;
        return;
    }

    if(r<=R && R<r+size && c<=C && C<c+size){
        int half = size/2;
        solution(r, c, half); // 왼쪽 위칸
        solution(r, c+half, half); // 오른쪽 위칸
        solution(r+half, c, half); // 왼쪽 아래칸
        solution(r+half, c+half, half); // 오른쪽 아래칸
    }
    else ans+=size*size;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin); // task /f /PID [pid]
	cin >> N >> R >> C; 
	solution(0, 0, 1<<N);
}