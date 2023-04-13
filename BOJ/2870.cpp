#include<iostream>
#include<string>
#include<queue>
using namespace std;

struct DATA{
    string s;
    bool operator < (const DATA &d) const {
        if(s.size() == d.s.size()) return s > d.s;
        return s.size() > d.s.size();
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N;
    cin >> N;

    priority_queue<DATA> pq;
    while (N--){
        string str; cin >> str;

        int start = -1, len = 0;
        for (int idx = 0; idx < (int)str.size(); idx++) {
            if('0' <= str[idx] && str[idx] <= '9'){ // 숫자인 경우
                if(start==-1 || len == 0 || (len==1 && str[idx-1]=='0')) { // 숫자의 시작
                    start = idx;
                    len = 1;
                }
                else len++; // 숫자의 중간

            }
            else{ 
                if(len!=0) pq.push({str.substr(start, len)}); // 문자인 경우
                len = 0;
            }
        }
        if(len!=0) pq.push({str.substr(start, len)});
    }

    while(!pq.empty()){
        cout << pq.top().s << "\n";
        pq.pop();
    }
}