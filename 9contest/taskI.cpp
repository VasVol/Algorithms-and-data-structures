#include <iostream>
#include <vector>
#include <algorithm>

void dfs(int v, const std::vector<std::vector<int>>& g,
         std::vector<bool>& used) {
  used[v] = true;
  for (int u : g[v]) {
    if (!used[u]) {
      dfs(u, g, used);
    }
  }
}

int main() {
  int l, r;
  std::cin >> l >> r;
  std::vector<std::vector<int>> g1(l);
  for (int i = 0; i < l; ++i) {
    int k;
    std::cin >> k;
    g1[i].resize(k);
    for (int j = 0; j < k; ++j) {
      std::cin >> g1[i][j];
      --g1[i][j];
      g1[i][j] += l;
    }
  }
  std::vector<int> a(l);
  for (int i = 0; i < l; ++i) {
    std::cin >> a[i];
    --a[i];
    a[i] += l;
  }
  std::vector<std::vector<int>> g(l + r);
  for (int v = 0; v < l; ++v) {
    for (int u : g1[v]) {
      if (a[v] == u) {
        g[u].push_back(v);
      } else {
        g[v].push_back(u);
      }
    }
  }
  std::vector<bool> used(l + r, false);
  for (int v = 0; v < l; ++v) {
    if ((a[v] == l - 1) && (!used[v])) {
      dfs(v, g, used);
    }
  }
  std::vector<int> left, right;
  for (int v = 0; v < l; ++v) {
    if (!used[v]) {
      left.push_back(v);
    }
  }
  for (int v = l; v < l + r; ++v) {
    if (used[v]) {
      right.push_back(v);
    }
  }
  std::cout << left.size() + right.size() << "\n";
  std::cout << left.size() << " ";
  for (int v : left) {
    std::cout << v + 1 << " ";
  }
  std::cout << "\n";
  std::cout << right.size() << " ";
  for (int u : right) {
    std::cout << u - l + 1 << " ";
  }
}
