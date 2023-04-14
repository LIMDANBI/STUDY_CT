#include <string>
#include <vector>

using namespace std;

bool possible(int n, long long val, vector<int> times)
{
  long long res = 0; // 검사할 수 있는 사람수
  for (int i = 0; i < (int)times.size(); i++)
    res += val / times[i];
  return n <= res;
}

long long solution(int n, vector<int> times)
{
  long long low = 0, mid, high = 1000000000000000;
  while (low <= high)
  {
    mid = (low + high) / 2;
    if (possible(n, mid, times))
      high = mid - 1;
    else
      low = mid + 1;
  }
  return low; // 모든 사람이 심사를 받는데 걸리는 시간의 최솟값
}