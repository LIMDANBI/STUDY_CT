#include<iostream>
#include<unordered_set>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    
    int N, M; 
    cin >> N >> M;

    string keword;
    unordered_set<string> memo; // hash set
    for(int i=0; i<N; i++){
        cin >> keword;
        memo.insert(keword);
    }

    string line;
    while(M--){ 
        cin >> line;
        
        int start = 0;
        while(start < line.size()){
            auto end = line.find(",", start);
            if(end == line.npos){ // , 가 없는 경우
                keword = line.substr(start);
                if(memo.find(keword)!=memo.end()) memo.erase(keword); // 메모장에 있는 키워드
                break;
            }
            else{
                keword = line.substr(start, end-start);
                if(memo.find(keword)!=memo.end()) memo.erase(keword);
                start = end+1;
            }
        }
        cout << memo.size() << "\n";
    }
}