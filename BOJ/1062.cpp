#include<iostream>
#include<algorithm>
#include<string>
#define MAX 51
using namespace std;

int N, K;
int ans = 0;
int kind = 0;
string word[MAX];
bool alphabet[27];
vector<int> alpha;
char must[5] = {'a', 'n', 't', 'i', 'c'}; // 반드시 알아야 하는 단어

int getReadCnt(int teach){
    int cnt = 0;
    for (int n = 0; n < N; n++){
        bool canRead = true;
        for (int i = 4; i < (int)word[n].size()-4; i++){
            int idx = word[n][i] - 'a';
            if ((teach & (1<<idx)) == 0) {canRead=false; break;}
        }
        if(canRead) cnt++;
    }
    return cnt;
}

void solution(int cnt, int idx, int teach){
    if(cnt == K || idx == (int)alpha.size()) {
        ans = max(ans, getReadCnt(teach));
        return;
    }

    solution(cnt + 1, idx + 1, teach | (1 << alpha[idx])); // 해당 알파벳 포함
    solution(cnt, idx+1, teach); // 미포함
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 5; i++) alphabet[must[i] - 'a'] = true; // init

    cin >> N >> K;
    for (int n = 0; n < N; n++) {
        cin >> word[n];
        for (int i = 4; i < (int)word[n].size()-4; i++) {
            int idx = word[n][i]-'a';
            if(alphabet[idx]) continue;
            alphabet[idx] = true;
            alpha.push_back(idx);
        }
    }

    if(K<5) cout << "0";
    else{
        int teach = 0;
        for (int i = 0; i < 5; i++) teach |= (1 << (must[i] - 'a'));
        solution(5, 0, teach);
        cout << ans;
    }
}