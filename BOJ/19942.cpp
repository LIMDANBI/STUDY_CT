#include<iostream>
#include<vector>
#define MAX 20
#define INF 1e9
using namespace std;

struct INGREDIENTS {int p, f, s, v, c;};

int N;
int minCost = INF;
int mp, mf, ms, mv; // 단백질, 지방, 탄수화물, 비타민의 최소 영양성분
INGREDIENTS ingredients[MAX]; // 식재료
vector<int> tmp, group; // 조건을 만족하는 식재료 집합

void input(){
    cin >> N;
    cin >> mp >> mf >> ms >> mv;
    for (int i = 0; i < N; i++){
        int p, f, s, v, c;
        cin >> p >> f >> s >> v >> c;
        ingredients[i] = (INGREDIENTS){p, f, s, v, c};
    }
}

void solve(int idx, int cost, int p, int f, int s, int v){

    // 1. 가지치기
    if(minCost <= cost) return; 

    // 2. 정답 갱신 및 가지치기
    if(mp<=p && mf<=f && ms<=s && mv<=v){
        minCost = cost;
        group.clear(); // init
        for(int num : tmp){
            group.push_back(num);
        }
        return; // 더 추가하면 비용만 증가
    }

    // 3. 종료 조건
    if(idx >= N) return;

    // 4. 포함하는 경우
    tmp.push_back(idx+1);
    auto ig = ingredients[idx];
    solve(idx + 1, cost + ig.c, p+ig.p, f+ig.f, s+ig.s, v+ig.v);
    tmp.pop_back();

    // 5. 포함하지 않는 경우
    solve(idx + 1, cost, p, f, s, v);
}

void output(){
    if(minCost == INF) cout << -1;
    else{
        cout << minCost << "\n";
        for(int num : group) cout << num << " ";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("../test/input.txt", "r", stdin);
    input();
    solve(0, 0, 0, 0, 0, 0);
    output();
}