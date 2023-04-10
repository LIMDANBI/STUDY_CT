#include<iostream>
#include<vector>
#include<unordered_map>
#define MAX 11
using namespace std;

int N, M;
bool broken[MAX];
int head[MAX], tail[MAX];

unordered_map<int, int> weight;   // (ID, 상자 무게)
unordered_map<int, int> beltNum; // (ID, bnum) | 물건 별 벨트 번호 (bnum=0, 사라진 것)
unordered_map<int, int> prv, nxt; // (ID, prv) (ID, nxt) | 해당 상자의 prv, nxt 관리

void set_up_factory(){
    cin >> N >> M;
    
    vector<int> id(N), ws(N); // N개의 상장의 id, 무게

    for (int i = 0; i < N; i++)
        cin >> id[i];
    for (int i = 0; i < N; i++)
        cin >> ws[i];

    // id마다 무게 관리, O(1)
    for (int i = 0; i < N; i++)
        weight[id[i]] = ws[i];
    
    // 벨트 별로 상자를 넣어줌
    int startIdx = 0;
    int beltSize = N / M;
    for (int i = 0; i < M; i++){
        head[i] = id[startIdx];
        tail[i] = id[startIdx + beltSize - 1];
        for (int j = startIdx; j < startIdx+beltSize; j++){
            beltNum[id[j]] = i + 1; // 상자 별 벨트 번호

            // prev, next 설정
            if (j < startIdx + beltSize - 1){ // 마지막 상자 nxt 없음!
                prv[id[j + 1]] = id[j];
                nxt[id[j]] = id[j + 1];
            }
        }
        startIdx += beltSize;
    }
}

void remove_id(int id, bool remove_belt){
    int b_num = beltNum[id] - 1;
    if(remove_belt) beltNum[id] = 0;

    if(head[b_num] == tail[b_num]) // 삭제 되는 게 1개
        head[b_num] = tail[b_num] = 0;
    else if(id == head[b_num]){ // 처음 상자 삭제
        int nid = nxt[id];
        head[b_num] = nid;
        prv[nid] = 0;
    }
    else if(id == tail[b_num]){ // 마지막 상자 삭제
        int pid = prv[id];
        tail[b_num] = pid;
        nxt[pid] = 0;
    }
    else{ // 중간 상자 삭제
        int pid = prv[id], nid = nxt[id];
        nxt[pid] = nid;
        prv[nid] = pid;
    }

    nxt[id] = prv[id] = 0;
}

void push_id(int target_id, int id){
    nxt[target_id] = id;
    prv[id] = target_id;

    int b_num = beltNum[target_id] - 1;
    if(tail[b_num] == target_id) tail[b_num] = id; // tail update
}

int down_object(int w_max){
    
    int w_sum = 0;
    for (int i = 0; i < M; i++){
        if(broken[i] || head[i] == 0) continue; // 망가진 벨트, 빈 벨트

        int id = head[i];
        int w = weight[id];

        if(w <= w_max){ // 하차
            w_sum += w;
            remove_id(id, true);
        }
        else if(nxt[id] != 0){ // 맨 뒤로 보냄
            remove_id(id, false);
            push_id(tail[i], id);
        }
    }
    return w_sum;
}

int reomove_object(int r_id){
    if(beltNum[r_id] == 0) return -1; // 이미 삭제된 상자

    remove_id(r_id, true); // 삭제
    return r_id;
}

int find_object(int f_id){

    if(beltNum[f_id]==0) // 이미 삭제된 상자
        return - 1;

    int b_num = beltNum[f_id] - 1;
    if(head[b_num] != f_id) { //head가 아닌 경우 앞으로!
        int origin_head = head[b_num];
        int origin_tail = tail[b_num];

        int now_tail = prv[f_id];
        tail[b_num] = now_tail;
        nxt[now_tail] = 0;

        nxt[origin_tail] = origin_head;
        prv[origin_head] = origin_tail;

        head[b_num] = f_id;
    }

    return b_num + 1;
}

int break_belt(int b_num){
    if(broken[b_num]) return -1; // 이미 고장난 경우

    broken[b_num] = true; // 고장처리 
    if(head[b_num] == 0) return b_num + 1; // 빈 벨트인 경우

    int nxt_num = b_num;
    while(true){
        nxt_num = (nxt_num + 1) % M;
        if(!broken[nxt_num] || nxt_num==b_num){

            if(tail[nxt_num]==0){ // 해당 벨트가 비어 있는 경우 (그대로 옮겨줌)
                head[nxt_num] = head[b_num];
                tail[nxt_num] = tail[b_num];
            }
            else{ // 해당 위치로 상자를 전부 옮겨줌
                push_id(tail[nxt_num], head[b_num]);
                tail[nxt_num] = tail[b_num];
            }

            int id = head[b_num];
            while(id !=0 ){ // belt num 갱신 
                beltNum[id] = nxt_num + 1;
                id = nxt[id];
            }

            head[b_num] = tail[b_num] = 0;
            break;
        }
    }

    return b_num + 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int q, cmd, w_max, r_id, f_id, b_num;
    cin >> q;
    while (q--){
        cin >> cmd;
        if(cmd == 100) set_up_factory();
        else if(cmd == 200){
            cin >> w_max;
            cout << down_object(w_max) << "\n";
        }
        else if(cmd == 300){
            cin >> r_id;
            cout << reomove_object(r_id) << "\n";
        }
        else if(cmd == 400){
            cin >> f_id;
            cout << find_object(f_id) << "\n";
        }
        else if(cmd == 500){
            cin >> b_num;
            cout << break_belt(b_num-1) << "\n";
        }
    }
}