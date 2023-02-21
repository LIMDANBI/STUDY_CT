#include<iostream>
#include<vector>
#define TC 4
#define COUNTRY 6
#define MATCHCNT 15
using namespace std;

int ans;
int match[COUNTRY][3]; // 경기 결과 (승 무 패)
int game[COUNTRY][3];
vector<pair<int, int> > team;

void make_team(){
    for(int team1=0; team1<COUNTRY; team1++){
        for(int team2=team1+1; team2<COUNTRY; team2++) team.push_back({team1, team2});
    }
}

void input(){
    for(int i=0; i<COUNTRY; i++){
        for(int j=0; j<3; j++){
            cin >> match[i][j];
            game[i][j] = 0;
        }
    }
}

bool check(){
    for(int i=0; i<COUNTRY; i++){
        for(int j=0; j<3; j++){
            if(match[i][j]!=game[i][j]) return false;
        }
    } return true;
}

void solution(int cnt){ // 6C2 = 15
    if(cnt == MATCHCNT){
        if(check()) ans = 1; // 하나라도 일치하는 경우
        return;
    }

    int t1 = team[cnt].first;
    int t2 = team[cnt].second;

    // 승 패
    game[t1][0]++; game[t2][2]++;
    solution(cnt+1);
    game[t1][0]--; game[t2][2]--;

    // 무승부
    game[t1][1]++; game[t2][1]++;
    solution(cnt+1);
    game[t1][1]--; game[t2][1]--;

    // 패 승
    game[t1][2]++; game[t2][0]++;
    solution(cnt+1);
    game[t1][2]--; game[t2][0]--;

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    make_team();

    for(int t=0; t<TC; t++){
        input();
        ans = 0;
        solution(0);
        cout << ans << " ";
    }
}