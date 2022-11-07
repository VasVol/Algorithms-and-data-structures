#include <iostream>
#include <vector>

void MakeDeg(std::vector<int>& deg, int n) {
  for (int i = 2; i <= n; ++i) {
    deg[i] = deg[i - 1];
    if ((i & (i - 1)) == 0) {
      ++deg[i];
    }
  }
}

void MakeSparse1(std::vector<std::vector<int>>& sparse1, std::vector<int>& a,
                 std::vector<int>& deg, int n) {
  for (int i = 0; i < n; ++i) {
    sparse1[0][i] = i;
  }
  for (int k = 0; k < deg[n]; ++k) {
    for (int i = 0; i < n; ++i) {
      int j = i + (1 << k);
      if (j >= n) {
        sparse1[k + 1][i] = sparse1[k][i];
        continue;
      }
      if (a[sparse1[k][i]] < a[sparse1[k][j]]) {
        sparse1[k + 1][i] = sparse1[k][i];
      } else {
        sparse1[k + 1][i] = sparse1[k][j];
      }
    }
  }
}

void MakeSparse2(std::vector<std::vector<int>>& sparse1, std::vector<int>& a,
                 std::vector<int>& deg, int n,
                 std::vector<std::vector<int>>& sparse2) {
  for (int i = 0; i < n; ++i) {
    sparse2[0][i] = i;
  }
  for (int i = 0; i < n - 1; ++i) {
    if (a[i] < a[i + 1]) {
      sparse2[1][i] = i + 1;
    } else {
      sparse2[1][i] = i;
    }
  }
  sparse2[1][n - 1] = n - 1;
  for (int k = 1; k < deg[n]; ++k) {
    for (int i = 0; i < n; ++i) {
      int j = i + (1 << k);
      if (j >= n) {
        sparse2[k + 1][i] = sparse2[k][i];
        continue;
      }
      if (a[sparse1[k][i]] <= a[sparse1[k][j]]) {
        if (a[sparse2[k][i]] < a[sparse1[k][j]]) {
          sparse2[k + 1][i] = sparse2[k][i];
        } else {
          sparse2[k + 1][i] = sparse1[k][j];
        }
      } else {
        if ((a[sparse1[k][i]] < a[sparse2[k][j]]) || (j == n - 1)) {
          sparse2[k + 1][i] = sparse1[k][i];
        } else {
          sparse2[k + 1][i] = sparse2[k][j];
        }
      }
    }
  }
}

void Solve(std::vector<std::vector<int>>& sparse1, std::vector<int>& a,
           std::vector<int>& deg, int m,
           std::vector<std::vector<int>>& sparse2) {
  for (int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l;
    --r;
    int k = deg[r - l + 1];
    int x = r - (1 << k) + 1;
    if (a[sparse1[k][l]] < a[sparse1[k][x]]) {
      std::cout << std::min(a[sparse2[k][l]], a[sparse1[k][x]]) << "\n";
    } else if (a[sparse1[k][l]] > a[sparse1[k][x]]) {
      std::cout << std::min(a[sparse1[k][l]], a[sparse2[k][x]]) << "\n";
    } else if (sparse1[k][l] == sparse1[k][x]) {
      std::cout << std::min(a[sparse2[k][l]], a[sparse2[k][x]]) << "\n";
    } else {
      std::cout << a[sparse1[k][l]] << "\n";
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> deg(n + 1, 0);
  MakeDeg(deg, n);

  std::vector<std::vector<int>> sparse1(deg[n] + 1, std::vector<int>(n));
  MakeSparse1(sparse1, a, deg, n);

  std::vector<std::vector<int>> sparse2(deg[n] + 1, std::vector<int>(n));
  MakeSparse2(sparse1, a, deg, n, sparse2);

  Solve(sparse1, a, deg, m, sparse2);
}
