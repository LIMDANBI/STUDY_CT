#include<iostream>
#include<cstring>
#define MAX 9 
using namespace std;

int N, M;
int arr[MAX];

void int_to_arr(int num){
    int idx = 0;
    while(num){
        arr[idx++] = num%10;
        num/=10;
    }
}

int get_arr_sum(){
    int res = 0;
    for(int a : arr) res+=a;
    return res;
}

int get_digit_root(int num){ // 숫자근 : 각 자릿수를 계속 더하여 한 자리 숫자를 만드는 것
    while(num > MAX){ // 한 자리 수가 될 때까지 반복
        int_to_arr(num);
        num = get_arr_sum();
        memset(arr, 0, sizeof(arr)); // 초기화
    }
    return num;
}

void solve(){ // 숫자근이 가장 큰 값을 찾는 프로그램
    int ans = 0, maxDigitRoot=-1;
    
    cin >> N;
    while(N--){
        cin >> M;
        int ditgitRoot = get_digit_root(M);
        if(maxDigitRoot < ditgitRoot){ // 더 큰 숫자근인 경우 값 갱신
            maxDigitRoot = ditgitRoot;
            ans = M;
        }
        if(maxDigitRoot == ditgitRoot){ // 가장 큰 숫자근이 여러 개이면 그 중 가장 작은 수를 출력
            ans = min(ans, M);
        }
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}