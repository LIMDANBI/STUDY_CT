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
    
    // row
    for(int c=0; c<N ; c++){
        
        int l=0;
        bool flag = true;
        bool upToDown = false;
        for(int r=0; r<N; r++){
            if(r!=0 && map[r-1][c] != map[r][c]){ // 이전 칸과 높이가 같지 않은 경우
                if(map[r-1][c]-map[r][c] == 1){ // \ (위->아래)
                    if(upToDown){ // 아직 이전 경사로를 놓지 못한 경우
                        flag = false;
                        break;
                    }
                    if(L!=1){
                        upToDown = true; // 위->아래 경사로 놓아야 함
                        l = 1;
                    }
                    else l = 0;
                }
                else if(map[r-1][c]-map[r][c] == -1){ // / (아래->위)
                    if(l>=L && !upToDown) l = 1; // 아래->위로 경사로를 놓을 수 있는 경우
                    else{ // 경사로를 놓을 수 없는 경우
                        flag = false;
                        break;
                    }
                }
                else{ // 한 칸 이상 차이
                    flag = false;
                    break;
                }
            }
            else{ // 이전 칸과 높이가 같은 경우
                l++;
                if(upToDown && l>=L){ // 위->아래로 경사로를 놓아야하고, 놓을 수 있는 경우
                    l = 0;
                    upToDown = false;
                }
            }
        }
        if(l<L && upToDown) flag = false; // 위-> 아래로 경사로를 완성하지 못하는 경우
        if(flag) ans++; // 지나갈 수 있는 경우
    }

    // col
    for(int r=0; r<N ; r++){ 

        int l=0;
        bool flag = true;
        bool leftToRight = false;
        for(int c=0; c<N; c++){
            if(c!=0 && map[r][c-1] != map[r][c]){ // 이전 칸과 높이가 같지 않은 경우
                if(map[r][c-1]-map[r][c] == 1){ // \ (왼->오)
                    if(leftToRight){ // 아직 이전 경사로를 놓지 못한 경우
                        flag = false;
                        break;
                    }
                    if(L!=1){
                        leftToRight = true; // 왼->오 경사로 놓아야 함
                        l = 1;
                    }
                    else l = 0;
                }
                else if(map[r][c-1]-map[r][c] == -1){ // / (오->왼)
                    if(l>=L && !leftToRight) l = 1; // 오->왼 경사로를 놓을 수 있는 경우
                    else{ // 경사로를 놓을 수 없는 경우
                        flag = false;
                        break;
                    }
                }
                else{ // 한 칸 이상 차이
                    flag = false;
                    break;
                }
            }
            else{ // 이전 칸과 높이가 같은 경우
                l++;
                if(leftToRight && l>=L){ // 오->왼 경사로를 놓아야하고, 놓을 수 있는 경우
                    l = 0;
                    leftToRight = false;
                }
            }
        }
        if(l<L && leftToRight) flag = false; // 왼->오 경사로를 완성하지 못하는 경우
        if(flag) ans++; // 지나갈 수 있는 경우
    }

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution();
}