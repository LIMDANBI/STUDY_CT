#include<vector>
#include<iostream>
#include<algorithm>
#define MAX 30001
using namespace std;

struct STUDENT{ int id, score; };

int N, score;
vector<STUDENT> student;

void input(){
    cin >> N;
    for (int id = 1; id <= N; id++){
        cin >> score;
        student.push_back({id, score});
    }
}

void swap(STUDENT *a, STUDENT*b){
    STUDENT *tmp = a;
    a = b; b = a;
}

void solve(){
    for (int i = 0; i < 3; i++){
        for (int j = i + 1; j < N; j++){
            if(student[i].score < student[j].score)
                swap(student[i], student[j]); // 내림차순
            else if(student[i].score == student[j].score){
                if(student[i].id > student[j].id)
                    swap(student[i], student[j]); // 오름차순
            }
        }
    }
}

void output(){
    for (int i = 0; i < 3; i++)
        cout << student[i].id << " ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
    output();
}