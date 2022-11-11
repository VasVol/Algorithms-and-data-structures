#include <iostream>
#include <vector>

int SortSelect(std::vector<int>& v, int begin, int end, int k) {
  for (int i = begin; i < end; ++i) {
    for (int j = i; j >= begin + 1; --j) {
      if (v[j - 1] > v[j]) {
        std::swap(v[j - 1], v[j]);
      } else {
        break;
      }
    }
  }
  return v[begin + k];
}

const int kBlockSize = 5;
int QuickSelect(std::vector<int>& v, size_t k) {
  if (v.size() <= kBlockSize - 1) {
    return SortSelect(v, 0, v.size(), k);
  }
  std::vector<int> medians;
  for (size_t i = 0; i + kBlockSize - 1 < v.size(); i += kBlockSize) {
    medians.push_back(SortSelect(v, i, i + kBlockSize, kBlockSize / 2));
  }
  int x = QuickSelect(medians, medians.size() / 2);
  std::vector<int> a, b;
  for (int elem : v) {
    if (elem < x) {
      a.push_back(elem);
    } else if (elem > x) {
      b.push_back(elem);
    }
  }
  if (k < a.size()) {
    return QuickSelect(a, k);
  }
  if (k + b.size() >= v.size()) {
    return QuickSelect(b, k - v.size() + b.size());
  }
  return x;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> v(n);
  std::cin >> v[0] >> v[1];
  for (int i = 2; i < n; ++i) {
    v[i] = (v[i - 1] * 123 + v[i - 2] * 45) % 10004321;
  }
  std::cout << QuickSelect(v, k - 1) << std::endl;
  return 0;
}
