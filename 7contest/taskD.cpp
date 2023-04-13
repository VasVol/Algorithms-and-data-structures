#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  int n_ = 0;
  int m_ = 0;
  std::vector<std::vector<int>> g_;
  std::vector<int> color_;
  std::vector<int> component_;
  std::vector<int> topo_sort_;

 public:
  Graph(const std::vector<std::pair<int, int>>& edges, bool oriented,
        int n, int m);
  void Dfs(int v, int k = 0);
  void Reverse();
  int Kosaraju();
  void Solve();
};

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].first >> edges[i].second;
  }
  Graph gr(edges, true, n, m);
  gr.Solve();
}

Graph::Graph(const std::vector<std::pair<int, int>>& edges, bool oriented,
             int n, int m) : n_(n), m_(m), g_(n_), color_(n_, 0),
             component_(n_, -1), topo_sort_(0) {
  for (auto edge : edges) {
    int x = edge.first - 1;
    int y = edge.second - 1;
    g_[x].push_back(y);
    if (!oriented) {
      g_[y].push_back(x);
    }
  }
}

void Graph::Dfs(int v, int k) {
  component_[v] = k;
  color_[v] = 1;
  for (int u : g_[v]) {
    if (color_[u] == 0) {
      Dfs(u, k);
    }
  }
  color_[v] = 2;
  topo_sort_.push_back(v);
}

void Graph::Reverse() {
  std::vector<std::vector<int>> ans(n_);
  for (int v = 0; v < n_; ++v) {
    for (int u : g_[v]) {
      ans[u].push_back(v);
    }
  }
  g_ = ans;
}

int Graph::Kosaraju() {
  for (int v = 0; v < n_; ++v) {
    if (color_[v] == 0) {
      Dfs(v);
    }
  }
  std::reverse(topo_sort_.begin(), topo_sort_.end());
  auto tmp = topo_sort_;
  Reverse();
  color_ = std::vector<int>(n_, 0);
  int k = 1;
  for (int v : tmp) {
    if (color_[v] == 0) {
      Dfs(v, k);
      ++k;
    }
  }
  return k - 1;
}

void Graph::Solve() {
  Kosaraju();
  for (int v = 0; v < n_; ++v) {
    std::cout << component_[v] << " ";
  }
}
