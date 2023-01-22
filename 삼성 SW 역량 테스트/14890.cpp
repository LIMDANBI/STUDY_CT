#include<iostream>
#define MAX 101
using namespace std;

int N, L;
int map[MAX][MAX];

void input(){
    cin >> N >> L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> map[i][j];
    }
}

void solution(){

    int ans = 0;
    
    // row check
    for(int r=0; r<N ; r++){
        
        int cnt=1;
        bool ismake = true;
        for(int c=0; c+1<N; c++){
            if(map[r][c] == map[r][c+1]) cnt++;
            else if(map[r][c]-map[r][c+1] == 1){ // 높이가 낮아지는 경우
                if(cnt >= 0) cnt = 1-L;
                else{
                    ismake = false;
                    break;
                }
            }
            else if(map[r][c]-map[r][c+1] == -1){ // 높이가 높아지는 경우
                if(cnt >= L) cnt = 1;
                else {
                    ismake = false;
                    break;
                }  
            }
            else { // 높이 차가 1 이상인 경우
                ismake = false;
                break;
            }
        }
        if(cnt>=0 && ismake) ans++;
    }

    // column check
    for(int c=0; c<N ; c++){ 

        int cnt=1;
        bool ismake = true;
        for(int r=0; r+1<N; r++){
            if(map[r][c] == map[r+1][c]) cnt++;
            else if(map[r][c]-map[r+1][c] == 1){ // 높이가 낮아지는 경우
                if(cnt >= 0) cnt = 1-L;
                else{
                    ismake = false;
                    break;
                }
            }
            else if(map[r][c]-map[r+1][c] == -1){ // 높이가 높아지는 경우
                if(cnt >= L) cnt = 1;
                else {
                    ismake = false;
                    break;
                } 
            }
            else { // 높이 차가 1 이상인 경우
                ismake = false;
                break;
            }
        }
        if(cnt>=0 && ismake) ans++;
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}