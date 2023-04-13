#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int MinimumNumberOfExperiments(int n, int k) {
  if (k == 0 && n > 1) {
    return -1;
  }
  if (k > std::log2(n)) {
    int p = 1;
    int ans = 0;
    while (p < n) {
      p *= 2;
      ++ans;
    }
    return ans;
  }
  // Пусть dp[i][j] - максимальная высота здания, которую можно
  // узнать, имея i самолетиков и j попыток.
  // Будем зранить dp[i] как dp1 и dp[i-1] как dp[0], потому что
  // для пересчета dp[i] нужен только dp[i-1].
  std::vector<int> dp0(n + 1, 0);
  std::vector<int> dp1(n + 1, 0);
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp1[j] = dp1[j - 1] + dp0[j - 1] + 1;
    }
    dp0.swap(dp1);
  }
  for (int j = 0; j <= n; ++j) {
    if (dp0[j] >= n - 1) {
      return j;
    }
  }
  return 0;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::cout << MinimumNumberOfExperiments(n, k);
}
