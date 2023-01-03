#include<iostream>
#include<cstring>
using namespace std;

bool ischeck[10];
int sdoku[10][10];

void input(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++) cin >> sdoku[i][j];
    }
}

int solution(){

    // row
    for(int j=0; j<9; j++){
        memset(ischeck, false, sizeof(ischeck));
        for(int i=0; i<9; i++){
            if(ischeck[sdoku[i][j]]) return 0;
            ischeck[sdoku[i][j]] = true;
        }
    }

    // col
    for(int i=0; i<9; i++){
        memset(ischeck, false, sizeof(ischeck));
        for(int j=0; j<9; j++){
            if(ischeck[sdoku[i][j]]) return 0;
            ischeck[sdoku[i][j]] = true;
        }
    }
    
    // small square
    for(int y=0; y<9; y+=3){
        for(int x=0; x<9; x+=3){
            memset(ischeck, false, sizeof(ischeck));
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    if(ischeck[sdoku[y+i][x+j]]) return 0;
                    ischeck[sdoku[y+i][x+j]] = true;
                }
            }
        }
    }

    return 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++){
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}