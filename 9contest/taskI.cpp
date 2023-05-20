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

void print_ans(int l, const std::vector<int>& left, const std::vector<int>& right) {
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

void minimum_vertex_coverage(int l, int r, const std::vector<std::vector<int>>& graph,
                             const std::vector<int>& matching) {
  std::vector<std::vector<int>> oriented_graph(l + r);
  for (int v = 0; v < l; ++v) {
    for (int u : graph[v]) {
      if (matching[v] == u) {
        oriented_graph[u].push_back(v);
      } else {
        oriented_graph[v].push_back(u);
      }
    }
  }
  std::vector<bool> used(l + r, false);
  for (int v = 0; v < l; ++v) {
    if ((matching[v] == l - 1) && (!used[v])) {
      dfs(v, oriented_graph, used);
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
  print_ans(l, left, right);
}

int main() {
  int l, r; // sizes of left and right graph parts
  std::cin >> l >> r;
  std::vector<std::vector<int>> graph(l);
  for (int i = 0; i < l; ++i) {
    int k;
    std::cin >> k;
    graph[i].resize(k);
    for (int j = 0; j < k; ++j) {
      std::cin >> graph[i][j];
      --graph[i][j];
      graph[i][j] += l;
    }
  }
  std::vector<int> matching(l);
  for (int i = 0; i < l; ++i) {
    std::cin >> matching[i];
    --matching[i];
    matching[i] += l;
  }
  minimum_vertex_coverage(l, r, graph, matching);
}
