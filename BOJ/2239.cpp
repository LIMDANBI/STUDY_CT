#include<iostream>
#include<vector>
#define MAX 9
using namespace std;

struct POS{int y, x;};

int sdoku[MAX][MAX];
vector<POS> zeros;

void input(){
    string line;
    for(int i=0; i<MAX; i++){
        cin >> line;
        for(int j=0; j<MAX; j++) {
            sdoku[i][j] = line[j]-'0';
            if(sdoku[i][j] == 0) zeros.push_back({i,j}); // 아직 숫자가 채워지지 않은 칸
        }
    }
}

bool promising(int y, int x, int num){
    int sy=y/3*3, sx=x/3*3;
    for(int i=0; i<MAX; i++){
        if(sdoku[i][x]==num) return false; // check row
        if(sdoku[y][i]==num) return false; // check column
        if(sdoku[sy+i/3][sx+i%3]==num) return false; // check 3*3 small square
    }
    return true;
}

void solution(int cnt){
    if(cnt == zeros.size()){
        for(int i=0; i<MAX; i++){
            for(int j=0; j<MAX; j++) cout << sdoku[i][j];
            cout << "\n";
        }
        exit(0);
    }

    int y = zeros[cnt].y, x = zeros[cnt].x;
    for(int num=1; num<=MAX; num++){ // 사전식으로 앞서는 것을 출력
        if(!promising(y, x, num)) continue;
        sdoku[y][x] = num;
        solution(cnt+1);
        sdoku[y][x] = 0; // recovery
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solution(0);
}