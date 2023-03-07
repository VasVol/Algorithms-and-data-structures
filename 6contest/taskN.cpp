#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Fast();
  std::string alpha, beta;
  std::cin >> alpha >> beta;
  long long len_a = alpha.size(), len_b = beta.size();
  long long k;
  std::cin >> k;
  if (std::abs(len_a - len_b) > k) {
    std::cout << -1;
    return 0;
  }
  std::vector<std::vector<std::vector<long long>>> dp(
    len_a + k + 1, std::vector<std::vector<long long>>(k + 1, std::vector<long long>(k + 1, 0)));
  for (long long i = 1; i <= len_a + k; ++i) {
    for (long long d = 0; d <= k; ++d) {
      for (long long a = 0; a <= k - d; ++a) {
        if (len_a - d + a < 0) {
          continue;
        }
        if ((i + d - a > len_a) || (i + d - a < 0)) {
          continue;
        }
        if (d > 0) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i][d - 1][a]);
        }
        if (a > 0) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i - 1][d][a - 1] + 1);
        }
        if ((i - a + d - 1 >= 0) && (i - 1 < len_b) && (i - a + d - 1 < len_a)) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i - 1][d][a] + (alpha[i - a + d - 1] == beta[i - 1]));
        }
      }
    }
  }
  long long ans = 0;
  for (long long d = 0; d <= k; ++d) {
    for (long long a = 0; a <= k - d; ++a) {
      if (len_a - d + a == len_b) {
        ans = std::max(ans, dp[len_b][d][a] + k - a - d);
      }
    }
  }
  std::cout << std::max(0ll, (len_b - ans));
}
