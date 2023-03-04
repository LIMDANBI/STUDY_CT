#include<iostream>
#include<string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int N; cin >> N;
	string balls; cin >> balls;

	int ans = 500001, idx, move;

    // move blue →
    idx=N-1; move=0;
    while(balls[idx]=='B') idx--;
    for(int i=0; i<idx; i++){ if(balls[i]=='B') move++; }
    ans = min(ans, move);

    // move blue ←
    idx=0; move=0;
    while(balls[idx]=='B') idx++;
    for(int i=idx; i<N; i++){ if(balls[i]=='B') move++; }
    ans = min(ans, move);

    // move red →
    idx=N-1; move=0;
    while(balls[idx]=='R') idx--;
    for(int i=0; i<idx; i++){ if(balls[i]=='R') move++; }
    ans = min(ans, move);

    // move red ←
    idx=0; move=0;
    while(balls[idx]=='R') idx++;
    for(int i=idx; i<N; i++){ if(balls[i]=='R') move++; }
    ans = min(ans, move);

	cout << ans;
}