#include<iostream>
#include<string>
#define UP 0
#define DOWN 1
#define FRONT 2
#define BACK 3
#define LEFT 4
#define RIGHT 5
using namespace std;

char face[3][3];
char cube[6][3][3];
string color = "wyrogb";

void init(){
    for(int i=0; i<6; i ++){
        for(int j=0; j<3; j++){
            for(int k=0; k<3; k++) cube[i][j][k] = color[i];
        }
    }
}

void up_cw(){
    char tmp[] = {cube[FRONT][0][0], cube[FRONT][0][1], cube[FRONT][0][2]};

    // UP
    for(int i=0; i<3; i++){for(int j=0; j<3; j++) face[j][2-i] = cube[UP][i][j];}
    for(int i=0; i<3; i++){for(int j=0; j<3; j++) cube[UP][i][j] = face[i][j];}


    // FRONT <- RIGHT
    cube[FRONT][0][0] = cube[RIGHT][0][0];
    cube[FRONT][0][1] = cube[RIGHT][0][1];
    cube[FRONT][0][2] = cube[RIGHT][0][2];

    // RIGHT <- BACK
    cube[RIGHT][0][0] = cube[BACK][0][0];
    cube[RIGHT][0][1] = cube[BACK][0][1];
    cube[RIGHT][0][2] = cube[BACK][0][2];

    // BACK <- LEFT
    cube[BACK][0][0] = cube[LEFT][0][0];
    cube[BACK][0][1] = cube[LEFT][0][1];
    cube[BACK][0][2] = cube[LEFT][0][2];

    // LEFT <- FRONT 
    cube[LEFT][0][0] = tmp[0];
    cube[LEFT][0][1] = tmp[1];
    cube[LEFT][0][2] = tmp[2];
}

void down_cw(){
    char tmp[] = {cube[FRONT][2][0], cube[FRONT][2][1], cube[FRONT][2][2]};
    
    // DOWN
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) face[j][2-i] = cube[DOWN][i][j];}
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) cube[DOWN][i][j] = face[i][j];}

    // FRONT <- LEFT
    cube[FRONT][2][0] = cube[LEFT][2][0];
    cube[FRONT][2][1] = cube[LEFT][2][1];
    cube[FRONT][2][2] = cube[LEFT][2][2];

    // LEFT <- BACK
    cube[LEFT][2][0] = cube[BACK][2][0];
    cube[LEFT][2][1] = cube[BACK][2][1];
    cube[LEFT][2][2] = cube[BACK][2][2];

    // BACK <- RIGHT
    cube[BACK][2][0] = cube[RIGHT][2][0];
    cube[BACK][2][1] = cube[RIGHT][2][1];
    cube[BACK][2][2] = cube[RIGHT][2][2];

    // RIGHT <- FRONT
    cube[RIGHT][2][0] = tmp[0];
    cube[RIGHT][2][1] = tmp[1];
    cube[RIGHT][2][2] = tmp[2];
}

void front_cw(){
    char tmp[] = {cube[UP][2][0], cube[UP][2][1], cube[UP][2][2]};

    // FRONT
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) face[j][2-i] = cube[FRONT][i][j];}
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) cube[FRONT][i][j] = face[i][j];}

    // UP <- LEFT
    cube[UP][2][0] = cube[LEFT][2][2];
    cube[UP][2][1] = cube[LEFT][1][2];
    cube[UP][2][2] = cube[LEFT][0][2];

    // LEFT <- DOWN
    cube[LEFT][2][2] = cube[DOWN][0][2];
    cube[LEFT][1][2] = cube[DOWN][0][1];
    cube[LEFT][0][2] = cube[DOWN][0][0];

    // DOWN <- RIGHT
    cube[DOWN][0][2] = cube[RIGHT][0][0];
    cube[DOWN][0][1] = cube[RIGHT][1][0];
    cube[DOWN][0][0] = cube[RIGHT][2][0];

    // RIGHT <- UP
    cube[RIGHT][0][0] = tmp[0];
    cube[RIGHT][1][0] = tmp[1];
    cube[RIGHT][2][0] = tmp[2];
}

void back_cw(){
    char tmp[] = {cube[UP][0][0], cube[UP][0][1], cube[UP][0][2]};

    // BACK
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) face[j][2-i] = cube[BACK][i][j];}
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) cube[BACK][i][j] = face[i][j];}

    // UP <- RIGHT
    cube[UP][0][0] = cube[RIGHT][0][2];
    cube[UP][0][1] = cube[RIGHT][1][2];
    cube[UP][0][2] = cube[RIGHT][2][2];

    // RIGHT <- DOWN
    cube[RIGHT][0][2] = cube[DOWN][2][2];
    cube[RIGHT][1][2] = cube[DOWN][2][1];
    cube[RIGHT][2][2] = cube[DOWN][2][0];

    // DOWN <- LEFT
    cube[DOWN][2][2] = cube[LEFT][2][0];
    cube[DOWN][2][1] = cube[LEFT][1][0];
    cube[DOWN][2][0] = cube[LEFT][0][0];

    // LEFT <- UP
    cube[LEFT][2][0] = tmp[0];
    cube[LEFT][1][0] = tmp[1];
    cube[LEFT][0][0] = tmp[2];
}

void left_cw(){
    char tmp[] = {cube[FRONT][0][0], cube[FRONT][1][0], cube[FRONT][2][0]};

    // LEFT
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) face[j][2-i] = cube[LEFT][i][j];}
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) cube[LEFT][i][j] = face[i][j];}
    
    // FRONT <- UP
    cube[FRONT][0][0] = cube[UP][0][0];
    cube[FRONT][1][0] = cube[UP][1][0];
    cube[FRONT][2][0] = cube[UP][2][0];

    // UP <- BACK
    cube[UP][0][0] = cube[BACK][2][2];
    cube[UP][1][0] = cube[BACK][1][2];
    cube[UP][2][0] = cube[BACK][0][2];

    // BACK <- DOWN
    cube[BACK][2][2] = cube[DOWN][0][0];
    cube[BACK][1][2] = cube[DOWN][1][0];
    cube[BACK][0][2] = cube[DOWN][2][0];

    // DOWN <- FRONT
    cube[DOWN][0][0] = tmp[0];
    cube[DOWN][1][0] = tmp[1];
    cube[DOWN][2][0] = tmp[2];
}

void right_cw(){
    char tmp[] = {cube[FRONT][0][2], cube[FRONT][1][2], cube[FRONT][2][2]};

    // RIGHT
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) face[j][2-i] = cube[RIGHT][i][j];}
    for(int i=0; i<3; i++){ for(int j=0; j<3; j++) cube[RIGHT][i][j] = face[i][j];}

    // FRONT <- DOWN
    cube[FRONT][0][2] = cube[DOWN][0][2];
    cube[FRONT][1][2] = cube[DOWN][1][2];
    cube[FRONT][2][2] = cube[DOWN][2][2];

    // DOWN <- BACK
    cube[DOWN][0][2] = cube[BACK][2][0];
    cube[DOWN][1][2] = cube[BACK][1][0];
    cube[DOWN][2][2] = cube[BACK][0][0];

    // BACK <- UP
    cube[BACK][2][0] = cube[UP][0][2];
    cube[BACK][1][0] = cube[UP][1][2];
    cube[BACK][0][0] = cube[UP][2][2];

    // UP <- FRONT
    cube[UP][0][2] = tmp[0];
    cube[UP][1][2] = tmp[1];
    cube[UP][2][2] = tmp[2];
}

void solution(){
    int N; cin >> N;

    string cmd; 
    char side, dir;
    while(N--){
        cin >> cmd; side = cmd[0]; dir = cmd[1];
        if(side=='U' && dir=='+') up_cw();
        else if(side=='U' && dir=='-') {up_cw(); up_cw(); up_cw();}
        else if(side=='D' && dir=='+') down_cw();
        else if(side=='D' && dir=='-') {down_cw(); down_cw(); down_cw();}
        else if(side=='F' && dir=='+') front_cw();
        else if(side=='F' && dir=='-') {front_cw(); front_cw(); front_cw();}
        else if(side=='B' && dir=='+') back_cw();
        else if(side=='B' && dir=='-') {back_cw(); back_cw(); back_cw();}
        else if(side=='L' && dir=='+') left_cw();
        else if(side=='L' && dir=='-') {left_cw(); left_cw(); left_cw();}
        else if(side=='R' && dir=='+') right_cw();
        else if(side=='R' && dir=='-') {right_cw(); right_cw(); right_cw();}
    }
}

void output(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) cout << cube[UP][i][j];
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while(T--){
        init();
        solution();
        output();
    }
}