#include<iostream>
#define MAX 105
using namespace std;

struct POS{int dir, dist;};
POS store[MAX];

int R, C, S;
int ddir, ddist;

void input(){
    cin >> C >> R;
    cin >> S;
    for(int i=0; i<S; i++){
        cin >> store[i].dir >> store[i].dist; 
    }
    cin >> ddir >> ddist;
}

void solve(){
    int ans = 0;

    for(int i=0; i<S; i++){
        int sdir = store[i].dir;
        int sdist = store[i].dist;

        int minDist = 0;

        // 1. 같은 방향에 있는 경우
        if(sdir == ddir){
            minDist = abs(sdist-ddist);
        }

        // 2. 반대 방향에 있는 경우
        else if((sdir==1 && ddir==2) || (sdir==2 && ddir==1) || (sdir==3 && ddir==4) || (sdir==4 && ddir==3)){
            if(ddir < 3){
                minDist+=R;
                minDist += min(sdist+ddist, C-sdist+C-ddist);
            }
            else{
                minDist+=C;
                minDist += min(sdist+ddist, R-sdist+R-ddist);
            }
        }

        // 3. 옆 방향에 있는 경우
        else {
            if(ddir==1){
                if(sdir==3) minDist = ddist + sdist;
                if(sdir==4) minDist = C-ddist + sdist;
            }
            else if(ddir==2){
                if(sdir==3) minDist = ddist + R-sdist;
                if(sdir==4) minDist = C-ddist + R-sdist;
            }
            else if(ddir==3){
                if(sdir==1) minDist = ddist + sdist;
                if(sdir==2) minDist = R-ddist + sdist;
            }
            else{
                if(sdir==1) minDist = ddist + C-sdist;
                if(sdir==2) minDist = R-ddist + C-sdist;
            }
        }
        ans += minDist;
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}