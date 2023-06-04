#include<iostream>
using namespace std;

struct Node{
    Node *prv = NULL;
    Node *nxt = NULL;
    int data;
};

Node *head, *tail; // dummy node 이용

void input(){
    int N, data; cin >> N;

    // init
    head = new Node();
    tail = new Node();
    head->nxt = tail;
    tail->prv = head;

    while(N--){
        cin >> data;
        
        Node *node = new Node();
        node->data = data;

        node->nxt = tail;
        node->prv = tail->prv;

        tail->prv = node;
        node->prv->nxt = node;
    }
}

void insert(){ // 앞에서부터 x의 위치 바로 다음에 y개의 숫자를 삽입
    int x, y, data; cin >> x >> y;
    
    Node *tmp = head;
    for (int i = 0; i < x; i++) tmp = tmp->nxt;

    while(y--){
        cin >> data;
        
        Node *node = new Node();
        node->data = data;

        node->prv = tmp;
        node->nxt = tmp->nxt;

        node->nxt->prv = node;
        node->prv->nxt = node;

        tmp = node; // update
    }
}

void del(){ // 앞에서부터 x의 위치 바로 다음부터 y개의 숫자를 삭제
    int x, y; cin >> x >> y;
    
    Node *tmp = head;
    for (int i = 0; i < x; i++) tmp = tmp->nxt;

    while(y--){
        Node *delNode = tmp->nxt;

        tmp->nxt = delNode->nxt;
        tmp->nxt->prv = tmp;

        delete delNode;
    }
}

void add(){ // 암호문의 맨 뒤에 y개의 숫자를 덧붙임
    int y, data; cin >> y;

    while(y--){
        cin >> data;

        Node *node = new Node();
        node->data = data;

        node->nxt = tail;
        node->prv = tail->prv;

        tail->prv = node;
        node->prv->nxt = node;
    }
}

void solution(){
    int M; cin >> M;

    char cmd;
    while (M--){
        cin >> cmd;
        if(cmd == 'I') insert(); // 삽입
        else if(cmd == 'D') del(); // 삭제
        else add(); // 추가
    }
}

void output(int t){
    cout << "#" << t << " ";

    Node *tmp = head;
    for (int i = 0; i < 10; i++){
        tmp = tmp->nxt;
        cout << tmp->data << " ";
    } cout << "\n";
}

int main(){
    freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int t = 1; t <= 10; t++){
        input();
        solution();
        output(t);
    }
}