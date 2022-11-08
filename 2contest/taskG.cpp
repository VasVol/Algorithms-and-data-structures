#include <iostream>
#include <vector>

int Byte(long long x, int idx) {
  const int kBytes = 8;
  const int kValuesInByte = 256;
  return (x >> (kBytes - 1 - idx) * kBytes) & (kValuesInByte - 1);
}

void StableByteSort(std::vector<long long>& v, int idx) {
  const int kValuesInByte = 256;
  std::vector<int> cnt(kValuesInByte);
  for (long long x : v) {
    ++cnt[Byte(x, idx)];
  }
  for (int i = 1; i < kValuesInByte; ++i) {
    cnt[i] += cnt[i - 1];
  }
  std::vector<long long> ans(v.size());
  for (int i = v.size() - 1; i >= 0; --i) {
    ans[--cnt[Byte(v[i], idx)]] = v[i];
  }
  v = ans;
}

void LSD(std::vector<long long>& v) {
  const int kBytes = 8;
  for (int idx = kBytes - 1; idx >= 0; --idx) {
    StableByteSort(v, idx);
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
