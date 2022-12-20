#include<iostream>
#include<deque>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    
    while(T--){
        string p; cin >> p;
        int size; cin >> size;
        string arr; cin >> arr;

        deque<int> dq;
        string num = "";
        for(int i=1; i<arr.size(); i++){
            if(arr[i]==']' || arr[i] == ',') {
                if(num == "") continue;
                dq.push_back(stoi(num));
                num = "";
            }
            else num+=arr[i];
        }
        
        bool isfront = true;
        bool isbreak = false;
        for(int i=0; i<p.size(); i++){
            if(p[i] == 'R') isfront = !isfront;
            else if(p[i] == 'D'){
                if(size == 0){
                    isbreak = true;
                    break;
                }
                if(isfront) dq.pop_front(); 
                else dq.pop_back();
                size--;
            }
        }

        if(isbreak) cout << "error" << "\n";
        else{
            cout << "[";
            if(isfront){
                while(size--){
                    if(size > 0) cout << dq.front() << ",";
                    else  cout << dq.front();
                    dq.pop_front();
                }
            }
            else{
                while(size--){
                    if(size > 0) cout << dq.back() << ",";
                    else  cout << dq.back();
                    dq.pop_back();
                }
            }
            cout << "]\n";
        }
    }
}