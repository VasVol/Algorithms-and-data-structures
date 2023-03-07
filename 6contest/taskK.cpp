#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> w(n + 1), c(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> w[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> c[i];
  }
  const int kInf = (1 << 30);
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -kInf));
  std::vector<std::vector<int>> ans(n + 1, std::vector<int>(m + 1, 0));
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int x = 0; x <= m; ++x) {
      if (x - w[i] >= 0 && dp[i - 1][x - w[i]] + c[i] > dp[i - 1][x]) {
        dp[i][x] = dp[i - 1][x - w[i]] + c[i];
        ans[i][x] = i;
      } else {
        dp[i][x] = dp[i - 1][x];
      }
    }
  }
  int x = std::max_element(dp[n].begin(), dp[n].end()) - dp[n].begin();
  int i = n;
  std::vector<int> answer;
  while (i > 0 && x > 0) {
    if (ans[i][x] != 0) {
      answer.push_back(i);
      x -= w[i];
    }
    i -= 1;
  }
  std::reverse(answer.begin(), answer.end());
  for (int idx : answer) {
    std::cout << idx << "\n";
  }
}
