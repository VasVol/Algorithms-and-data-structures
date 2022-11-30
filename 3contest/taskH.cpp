#include <iostream>
#include <vector>

class SparseTable {
 private:
  std::vector<int> values_;
  std::vector<std::vector<int>> min_indexes_;
  std::vector<int> deg_;
  void MakeDeg(int n);
  int MinElement(const std::vector<int>& a);

 public:
  SparseTable(const std::vector<int>& a);
  int MinIdx(int l, int r);
  int SecondMinIdx(int l, int r);
};

void SparseTable::MakeDeg(int n) {
  deg_.resize(n + 1, 0);
  for (int i = 2; i <= n; ++i) {
    deg_[i] = deg_[i - 1];
    if ((i & (i - 1)) == 0) {
      ++deg_[i];
    }
  }
}

SparseTable::SparseTable(const std::vector<int>& a) {
  values_ = a;
  int n = static_cast<int>(a.size());
  MakeDeg(n);
  min_indexes_.resize(deg_[n] + 1, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    min_indexes_[0][i] = i;
  }
  for (int k = 0; k < deg_[n]; ++k) {
    for (int i = 0; i < n; ++i) {
      int j = i + (1 << k);
      if (j >= n) {
        min_indexes_[k + 1][i] = min_indexes_[k][i];
        continue;
      }
      if (a[min_indexes_[k][i]] < a[min_indexes_[k][j]]) {
        min_indexes_[k + 1][i] = min_indexes_[k][i];
      } else {
        min_indexes_[k + 1][i] = min_indexes_[k][j];
      }
    }
  }
}

int SparseTable::MinElement(const std::vector<int>& a) {
  int ans = a[0];
  for (int x : a) {
    if (values_[x] < values_[ans]) {
      ans = x;
    }
  }
  return ans;
}

int SparseTable::MinIdx(int l, int r) {
  int k = deg_[r - l + 1];
  int x = r - (1 << k) + 1;
  std::vector<int> ans = {min_indexes_[k][l], min_indexes_[k][x]};
  return MinElement(ans);
}

int SparseTable::SecondMinIdx(int l, int r) {
  int i = MinIdx(l, r);
  std::vector<int> ans;
  if (l <= i - 1) {
    ans.push_back(MinIdx(l, i - 1));
  }
  if (i + 1 <= r) {
    ans.push_back(MinIdx(i + 1, r));
  }
  return MinElement(ans);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  SparseTable sp(a);
  for (int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    std::cout << a[sp.SecondMinIdx(l - 1, r - 1)] << "\n";
  }
}
