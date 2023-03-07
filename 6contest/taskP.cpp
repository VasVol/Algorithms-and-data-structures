#include <algorithm>
#include <iostream>
#include <vector>

int Bit(int mask, int pos) { return (mask >> pos) & 1; }

bool Ok(int mask, const std::vector<int>& v, int n) {
  for (int i = 0; i < n; ++i) {
    if ((v[i] != 2) && (v[i] != Bit(mask, i))) {
      return false;
    }
  }
  return true;
}

std::vector<int> PrevMasks(int mask, int n) {
  std::vector<int> ans;
  for (int k = 0; k <= 1; ++k) {
    bool flag = true;
    int x = k;
    for (int i = 1; i < n; ++i) {
      int new_bit = 2 - Bit(mask, i) - Bit(mask, i - 1) - Bit(x, i - 1);
      if ((new_bit != 0) && (new_bit != 1)) {
        flag = false;
        break;
      }
      x += (new_bit << i);
    }
    if (flag) {
      ans.push_back(x);
    }
  }
  return ans;
}

int main() {
  int mod = 1'000'000'007;
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> v(m, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      std::cin >> c;
      if (c == '+') {
        v[j][i] = 1;
      } else if (c == '-') {
        v[j][i] = 0;
      } else {
        v[j][i] = 2;
      }
    }
  }
  std::vector<std::vector<int>> dp(m, std::vector<int>(1 << n, 0));
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (Ok(mask, v[0], n)) {
      dp[0][mask] = 1;
    }
  }
  for (int i = 1; i < m; ++i) {
    for (int mask = 0; mask < (1 << n); ++mask) {
      if (!Ok(mask, v[i], n)) {
        continue;
      }
      std::vector<int> prev_masks = PrevMasks(mask, n);
      for (int prev_mask : prev_masks) {
        if (Ok(prev_mask, v[i - 1], n)) {
          dp[i][mask] += dp[i - 1][prev_mask];
          dp[i][mask] %= mod;
        }
      }
    }
  }
  int ans = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    ans += dp[m - 1][mask];
    ans %= mod;
  }
  std::cout << ans << "\n";
}
