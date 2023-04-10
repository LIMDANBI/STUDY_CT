#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;

int N, M;
int cntGift[MAX]; // 해당 벨트의 선물 개수
int prv[MAX], nxt[MAX]; // id의 prv, nxt
int head[MAX], tail[MAX]; // belt의 head, tail

// 100
void set_up_factory(){
    cin >> N >> M; // N개의 벨트, M개의 선물

    int b_num;
    for (int id = 1; id <= M; id++){
        cin >> b_num; b_num--;
        cntGift[b_num]++;
        
        if(head[b_num] == 0) // 처음 물건인 경우
            head[b_num] = tail[b_num] = id;
        else{
            int orgin_tail = tail[b_num];
            prv[id] = orgin_tail;
            nxt[orgin_tail] = id;
            tail[b_num] = id;
        }
    }
}

// 200
int move_all(int src, int dst){ // dst번째 벨트에 있는 선물들의 개수 반환

    if(cntGift[src]==0) return cntGift[dst];

    cntGift[dst] += cntGift[src];
    cntGift[src] = 0;

    int src_head = head[src];
    int src_tail = tail[src];
    int dst_head = head[dst];

    head[dst] = src_head;
    if(tail[dst] == 0) tail[dst] = src_tail;
    nxt[src_tail] = dst_head;
    prv[dst_head] = src_tail;

    head[src] = tail[src] = 0;
    return cntGift[dst];
}

// 300
int change_front(int src, int dst){ // dst번째 벨트에 있는 선물들의 개수 반환

    int src_head = head[src];
    int dst_head = head[dst];

    if(src_head == 0 && dst_head == 0) return cntGift[dst]; // 둘다 비어있는 경우

    if(src_head == 0) { // src 벨트가 비어 있는 경우 
        cntGift[src]++;
        cntGift[dst]--;
        
        head[src] = tail[src] = dst_head;
        if(nxt[dst_head]!=0) head[dst] = nxt[dst_head];
        else head[dst] = tail[dst] = 0;
        prv[head[dst]] = nxt[dst_head] = 0;
    }
    else if(dst_head == 0){ // dst 벨트가 비어 있는 경우
        cntGift[src]--;
        cntGift[dst]++;       
        
        head[dst] = tail[dst] = src_head;
        if(nxt[src_head]!=0) head[src] = nxt[src_head];
        else head[src] = tail[src] = 0;
        prv[head[src]] = nxt[src_head] = 0;
    }
    else{ // 두 벨트 모두 비어 있지 않은 경우

        int src_nxt = nxt[src_head];
        int dst_nxt = nxt[dst_head];

        nxt[src_head] = dst_nxt;
        prv[dst_nxt] = src_head;

        nxt[dst_head] = src_nxt;
        prv[src_nxt] = dst_head;

        if(head[src] == tail[src]) head[src] = tail[src] = dst_head;
        else head[src] = dst_head;

        if(head[dst] == tail[dst]) head[dst] = tail[dst] = src_head;
        else head[dst] = src_head;
    }

    return cntGift[dst];
}

// 400
int divide(int src, int dst){ // dst번째 벨트에 있는 선물들의 개수 반환

    if(cntGift[src] <= 1) return cntGift[dst]; // 옮겨지지 않는 경우

    int movedCnt = cntGift[src] / 2;
    cntGift[src] -= movedCnt;
    cntGift[dst] += movedCnt;

    int src_head = head[src];
    int dst_head = head[dst];
    int lastGift = head[src];
    
    while(--movedCnt) lastGift = nxt[lastGift];
    int new_head = nxt[lastGift];

    head[src] = new_head;
    prv[new_head] = 0;

    if(dst_head == 0){
        head[dst] = src_head;
        tail[dst] = lastGift;
        prv[src_head] = 0;
        nxt[lastGift] = 0;
    }
    else{
        prv[dst_head] = lastGift;
        nxt[lastGift] = dst_head;
        head[dst] = src_head;
    }

    return cntGift[dst];
}

// 500
int get_info(int p_num){ // a + 2 * b 반환 (a: 앞 선물 번호, b: 뒤 선물 번호)
    int a = prv[p_num] == 0 ? -1 : prv[p_num];
    int b = nxt[p_num] == 0 ? -1 : nxt[p_num];
    return a + 2 * b;
}

// 600
int get_belt(int b_num){ // a + 2*b + 3*c의 값을 출력 (a: 앞 선물 번호, b: 뒤 선물 번호, c : 해당 벨트 내 선물 개수)

    int a = head[b_num] == 0 ? -1 : head[b_num];
    int b = tail[b_num] == 0 ? -1 : tail[b_num];
    int c = cntGift[b_num];

    return a + 2 * b + 3 * c;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int q; cin >> q;
    int cmd, src=0, dst=0, p_num, b_num;
    while (q--) {
        cin >> cmd;
        if(cmd == 100) set_up_factory(); // 공장 설립
        else if(cmd == 200){ // 물건 모두 옮기기
            cin >> src >> dst;
            cout << move_all(src - 1, dst - 1) << "\n";
        }
        else if(cmd == 300){ // 앞 물건만 교체하기
            cin >> src >> dst;
            cout << change_front(src - 1, dst - 1) << "\n";
        }
        else if(cmd == 400){ // 물건 나누기
            cin >> src >> dst;
            cout << divide(src - 1, dst - 1) << "\n";
        }
        else if(cmd == 500){ // 선물 정보 얻기
            cin >> p_num;
            cout << get_info(p_num) << "\n";
        }
        else if(cmd == 600){ // 벨트 정보 얻기
            cin >> b_num;
            cout << get_belt(b_num - 1) << "\n";
        }
    }
}