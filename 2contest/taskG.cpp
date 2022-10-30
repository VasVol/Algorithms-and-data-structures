#include <iostream>
#include <vector>

int Byte(long long x, int idx) { return (x >> (7 - idx) * 8) & 255; }

std::vector<long long> StableByteSort(std::vector<long long>& v, int idx) {
  std::vector<int> cnt(256);
  for (long long x : v) {
    ++cnt[Byte(x, idx)];
  }
  for (int i = 1; i < 256; ++i) {
    cnt[i] += cnt[i - 1];
  }
  std::vector<long long> ans(v.size());
  for (int i = v.size() - 1; i >= 0; --i) {
    ans[--cnt[Byte(v[i], idx)]] = v[i];
  }
  return ans;
}

void LSD(std::vector<long long>& v) {
  for (int idx = 7; idx >= 0; --idx) {
    v = StableByteSort(v, idx);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  std::cin >> n;
  std::vector<long long> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  LSD(v);
  for (int i = 0; i < n; ++i) {
    std::cout << v[i] << "\n";
  }
  return 0;
}
