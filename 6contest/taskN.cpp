#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

long long Solve(std::string alpha, std::string beta, long long k) {
  long long len_a = alpha.size(), len_b = beta.size();
  if (std::abs(len_a - len_b) > k) {
    return -1;
  }
  // dp[i][d][a] - максимальное количество совпавших позиций с префиксом строки beta длины i,
  // если из какого-то префикса строки alpha сделали строку длины i, сделав d удалений и a добавлений
  // избавляемся от первого индекса i, потому что используем только dp[i-1] и dp[i]-й при подсчете dp[i]
  // поэтому в итоге храним только предыдущий данный dp2 и предыдущий dp1, и ещё dp_len_b, что соответствует
  // dp[len_b], для подсчета ответа
  std::vector<std::vector<long long>> dp1(k + 1, std::vector<long long>(k + 1, 0));
  auto dp2 = dp1;
  auto dp_len_b = dp1;
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
          dp2[d][a] = std::max(dp2[d][a], dp2[d - 1][a]);
        }
        if (a > 0) {
          dp2[d][a] = std::max(dp2[d][a], dp1[d][a - 1] + 1);
        }
        if ((i - a + d - 1 >= 0) && (i - 1 < len_b) && (i - a + d - 1 < len_a)) {
          dp2[d][a] = std::max(dp2[d][a], dp1[d][a] + (alpha[i - a + d - 1] == beta[i - 1]));
        }
      }
    }
    dp1 = dp2;
    if (i == len_b) {
      dp_len_b = dp2;
    }
  }
  long long ans = 0;
  for (long long d = 0; d <= k; ++d) {
    for (long long a = 0; a <= k - d; ++a) {
      if (len_a - d + a == len_b) {
        ans = std::max(ans, dp_len_b[d][a] + k - a - d);
      }
    }
  }
  return std::max(0ll, (len_b - ans));
}

int main() {
  Fast();
  std::string alpha, beta;
  std::cin >> alpha >> beta;
  long long k;
  std::cin >> k;
  std::cout << Solve(alpha, beta, k);
}
