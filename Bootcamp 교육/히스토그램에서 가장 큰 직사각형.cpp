#include<iostream>
#include<stack>
#define MAX 100005
using namespace std;

struct DATA{int idx; long long h;};

int N; //히스토그램수
int H[MAX]; //히스토그램 높이

void input(){
    for(int i=0; i<N; i++) cin >> H[i];
}

long long getMaxArea(){ // 히스토그램에서 가장 큰 직사각형의 넓이
    long long res=0, ph;
    int pidx = 0;
    
    stack<DATA> s; // 직사각형을 그릴 수 있는 정보 저장
    for(int idx=0; idx<N; idx++){
        bool is_low = false;
        while(!s.empty() && s.top().h > H[idx]){ // 낮아지는 경우
            pidx = s.top().idx;
            ph = s.top().h;
            is_low = true;
            res = max(res, (idx-pidx)*ph); // 계산하고
            s.pop(); // 제거
        }
        if(is_low) s.push({pidx, H[idx]}); // 낮아지는 경우
        else s.push({idx, H[idx]}); // 같거나 높아지는 경우
    }

    // 스택이 남아있는 경우
    while (s.empty()){
        s.pop();
    }
    

    return res;
}

void solve(){
    while(true){ // 여러 개의 TC
        cin >> N;
        if(N == 0) break; // 종료 조건
        input();
        cout << getMaxArea() << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}