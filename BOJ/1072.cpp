#include<iostream>
using namespace std;

long long X, Y, Z;

bool ischange(int cnt){
    long long new_Z = (Y+cnt)*100/(X+cnt);
    if(new_Z!=Z) return true; // Z가 변하는 경우
    return false;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> X >> Y;

    Z = Y*100/X; // 형택이의 승률
    int low=0, mid, high = X;
    while(low<=high){
        mid = (low+high)/2;
        if(ischange(mid)) high=mid-1;
        else low=mid+1;
    }
    low>X ? cout << -1 : cout << low;// Z가 절대 변하지 않는 경우, -1 출력
}