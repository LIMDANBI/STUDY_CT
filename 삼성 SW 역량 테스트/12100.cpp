#include<iostream>
#include<vector>
#define MAX 21
#define CNT 5
using namespace std;

int N, ans=0;
int dir[CNT];
vector<int> tmp;
int map[MAX][MAX], init_map[MAX][MAX];

void input(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> init_map[i][j];
    }
}

int get_max_val(){
    int res = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) res = max(res, map[i][j]);
    } return res;
}

void move_up(){
    for(int c=0; c<N; c++){

        tmp.clear();
        for(int r=0; r<N; r++){
            if(map[r][c]!=0) tmp.push_back(map[r][c]);
            map[r][c] = 0;
        }

        int r=0, idx=0;
        while(idx < tmp.size()){
            if(idx+1 < tmp.size() && tmp[idx] == tmp[idx+1]){
                map[r++][c] = tmp[idx]*2;
                idx+=2;
            }
            else map[r++][c] = tmp[idx++];
        }
    }
}

void move_down(){
    for(int c=0; c<N; c++){

        tmp.clear();
        for(int r=N-1; r>=0; r--){
            if(map[r][c]!=0) tmp.push_back(map[r][c]);
            map[r][c] = 0;
        }

        int r=N-1, idx=0;
        while(idx < tmp.size()){
            if(idx+1 < tmp.size() && tmp[idx] == tmp[idx+1]){
                map[r--][c] = tmp[idx]*2;
                idx+=2;
            }
            else map[r--][c] = tmp[idx++];
        }
    }
}

void move_left(){
    for(int r=0; r<N; r++){

        tmp.clear();
        for(int c=0; c<N; c++){
            if(map[r][c]!=0) tmp.push_back(map[r][c]);
            map[r][c] = 0;
        }

        int c=0, idx=0;
        while(idx < tmp.size()){
            if(idx+1 < tmp.size() && tmp[idx] == tmp[idx+1]){
                map[r][c++] = tmp[idx]*2;
                idx+=2;
            }
            else map[r][c++] = tmp[idx++];
        }
    }
}

void move_right(){
    for(int r=0; r<N; r++){

        tmp.clear();
        for(int c=N-1; c>=0; c--){
            if(map[r][c]!=0) tmp.push_back(map[r][c]);
            map[r][c] = 0;
        }

        int c=N-1, idx=0;
        while(idx < tmp.size()){
            if(idx+1 < tmp.size() && tmp[idx] == tmp[idx+1]){
                map[r][c--] = tmp[idx]*2;
                idx+=2;
            }
            else map[r][c--] = tmp[idx++];
        }
    }
}

void solution(int cnt){
    if(cnt == CNT){ // 최대 5번 이동시켜서 얻을 수 있는 가장 큰 블록 출력
        
         // copy map
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++) map[i][j] = init_map[i][j];
        }

        // move
        for(int i=0; i<CNT; i++){
            if(dir[i]==0) move_up();
            else if(dir[i]==1) move_down();
            else if(dir[i]==2) move_left();
            else move_right();
        }

        // ans update
        ans = max(ans, get_max_val());
        return;
    }
    for(int i=0; i<4; i++){
        dir[cnt] = i; // 이동 방향 지정
        solution(cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(0);
    cout << ans;
}