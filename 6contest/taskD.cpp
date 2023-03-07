#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;
  if (k == 0 && n > 1) {
    std::cout << -1;
    return 0;
  }
  if (k > std::log2(n) + 10) {
    int p = 1;
    int ans = 0;
    while (p < n) {
      p *= 2;
      ++ans;
    }
    std::cout << ans;
    return 0;
  }
  std::vector<int> dp0(n + 1, 0);
  std::vector<int> dp1(n + 1, 0);
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp1[j] = dp1[j - 1] + dp0[j - 1] + 1;
    }
    dp0 = dp1;
  }
  for (int j = 0; j <= n; ++j) {
    if (dp0[j] >= n - 1) {
      std::cout << j;
      return 0;
    }
  }
}
