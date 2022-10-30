#include <iostream>
#include <vector>

int SortSelect(std::vector<int>& v, int k) {
  for (int i = 1; i < (int)v.size(); ++i) {
    for (int j = i; j >= 1; --j) {
      if (v[j - 1] > v[j]) {
        std::swap(v[j - 1], v[j]);
      } else {
        break;
      }
    }
  }
  return v[k];
}

int QuickSelect(std::vector<int>& v, int k) {
  int p = 10;
  if ((int)v.size() <= p - 1) {
    return SortSelect(v, k);
  }
  std::vector<int> medians;
  for (int i = 0; i + p - 1 < (int)v.size(); i += p) {
    auto a = std::vector<int>(v.begin() + i, v.begin() + i + p);
    medians.push_back(SortSelect(a, a.size() / 2));
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
  if (k < (int)a.size()) {
    return QuickSelect(a, k);
  }
  if (k >= (int)v.size() - (int)b.size()) {
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
