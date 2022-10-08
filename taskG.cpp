#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << std::fixed;
  std::cout << std::setprecision(10);
  int n;
  std::cin >> n;
  auto a = new double[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  auto p = new double[n + 1];
  p[0] = 0;
  for (int i = 1; i <= n; ++i) {
    p[i] = p[i - 1] + log2(a[i - 1]);
  }
  int q;
  std::cin >> q;
  for (int t = 0; t < q; ++t) {
    int i, j;
    std::cin >> i >> j;
    std::cout << pow(2, (p[j + 1] - p[i]) / (j - i + 1)) << "\n";
  }
  delete[] a;
  delete[] p;
  return 0;
}
