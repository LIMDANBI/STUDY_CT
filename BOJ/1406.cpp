#include<iostream>
#include<string>
using namespace std;

struct Node {
	Node *prev = NULL;
	char data;
	Node *next = NULL;
};

Node *head = new Node();
Node *tail = head;
Node *cur;

void make_linked_list() {
	string str; cin >> str;
	for (int i = 0; i < str.size(); i++) {
		Node *node = new Node();
		node->data = str[i];
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	cur = tail;
}

void move_left() { // 커서를 왼쪽으로 한 칸 옮김
	if (cur != head) cur = cur->prev; // 커서가 문장의 맨 앞이면 무시
}

void move_right() { // 커서를 오른쪽으로 한 칸 옮김
	if (cur != tail) cur = cur->next; // 커서가 문장의 맨 뒤이면 무시
}

void delete_char() { // 커서 왼쪽에 있는 문자를 삭제
	if (cur == head) return;
	if (cur == tail) {
		tail = cur->prev;
		tail->next = NULL;
		cur = tail;
	}
	else {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		cur = cur->prev;
	}
}

void add_char(char data) { // 문자(data)를 커서 왼쪽에 추가
	
	Node *n = new Node();
	n->data = data;
	
	if (cur == tail) tail = n;
	else {
		n->next = cur->next;
		cur->next->prev = n;
	}
	n->prev = cur;
    cur->next = n;
	cur = n;
}

void excute_command() {
	int M;  cin >> M;
	char cmd, data;

	while(M--) {
		cin >> cmd;
		if (cmd == 'L') move_left();
		else if (cmd == 'D') move_right();
		else if (cmd == 'B') delete_char();
		else if (cmd == 'P') {
			cin >> data;
			add_char(data);
		}
	}
}

void output() {
	for (Node *n = head->next; n != NULL; n = n->next) cout << n->data;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
	make_linked_list();
	excute_command();
	output();
}