#include<iostream>
#include<vector>
#define MAX 51
using namespace std;

int N, len;
vector<int> v;
bool isuse[MAX];

void solution(string seq){
    if(seq == "") {
        for(int i=0; i<v.size(); i++) cout << v[i] << " ";
        exit(0); // 종료 조건
    }

    int num;
    for(int i=1; i<=2; i++){
        num = stoi(seq.substr(0, i));
        if(num<=len && !isuse[num]){
            isuse[num] = true;
            v.push_back(num);
            solution(seq.substr(i, seq.size()-i));
            isuse[num] = false;
            v.pop_back();
        }
        if(seq.size() == i) break;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string seq; cin >> seq;
    len = seq.size();
    if(len>9) len -= (len-9)/2;
    solution(seq);
}