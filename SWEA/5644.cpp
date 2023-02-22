#include<iostream>
#include<queue>
#define TIME 101
using namespace std;

struct BC{int y, x, c, p;};
vector<BC> bc;

int M, A;
int pathA[TIME], pathB[TIME];
int dy[] = { 0, -1, 0, 1, 0 }; // 이동x 상 우 하 좌
int dx[] = { 0, 0, 1, 0, -1 };


void input() {
    cin >> M >> A; // 총 이동 시간, BC의 개수
    for (int i = 0; i < M; i++) cin >> pathA[i]; // 사용자 A의 이동 정보
    for (int i = 0; i < M; i++) cin >> pathB[i]; // 사용자 B의 이동 정보

    int y, x, c, p;
    for (int i = 0; i < A; i++) { // BC의 정보
        cin >> x >> y >> c >> p; // 좌표(X, Y), 충전 범위(C), 처리량(P)
        bc.push_back({y, x, c, p});
    }
}

vector<int> get_possible_charge(int y, int x){
    vector<int> res;
    for(int i=0; i<A; i++){
        if(abs(y-bc[i].y)+abs(x-bc[i].x) <= bc[i].c) res.push_back(i);
    } return res;
}

int solution() { //  모든 사용자의 충전량 합의 최대값

    int ans = 0;
    int ay, ax, by, bx;
    ay = ax = 1; by = bx = 10;

    int da, db; // a, b의 이동방향 
    for(int i=-1; i<M; i++){ // 사용자는 초기 위치(0초)부터 충전할 수 있음 
        
        if(0<=i){ 
            da = pathA[i]; ay+=dy[da]; ax+=dx[da]; // a 이동
            db = pathB[i]; by+=dy[db]; bx+=dx[db]; // b 이동
        }

        if(ay==by && ax==bx){ // 두 사용자의 위치가 같은 경우 
            vector<int> pab = get_possible_charge(ay, ax);
            if(pab.size() == 0) continue; // 0개
            else if(pab.size()==1) ans+=bc[pab[0]].p; // 1개
            else{ // 2개 이상
                priority_queue<int> pq;
                for(int a=0; a<pab.size(); a++) pq.push(bc[pab[a]].p);
                ans+=pq.top(); pq.pop(); // first
                ans+=pq.top(); // second
            }
        }
        else{ // 위치가 다른 경우

            vector<int> pa = get_possible_charge(ay, ax); // a 충전
            vector<int> pb = get_possible_charge(by, bx); // b 충전

            // 최대가 되는 조합을 찾음
            priority_queue<int> pq;
            for(int a=0; a<pa.size(); a++) pq.push(bc[pa[a]].p);
            for(int b=0; b<pb.size(); b++) pq.push(bc[pb[b]].p);
            for(int a=0; a<pa.size(); a++) {
                for(int b=0; b<pb.size(); b++){
                    if(pa[a]!=pb[b]) pq.push(bc[pa[a]].p+bc[pb[b]].p);
                }
            }
            if(!pq.empty()) ans+=pq.top();
        }
    } 
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T; // 테스트 케이스의 개수 T
    for (int t = 1; t <= T; t++) {
        bc.clear(); // init
        input();
        cout << "#" << t << " " << solution() << "\n";
    }
}