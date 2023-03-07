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
  Graph(bool oriented);
  void Dfs(int v, int k = 0);
  void Reverse();
  void Kosaraju();
};

int main() {
  Graph gr(true);
  gr.Kosaraju();
}

Graph::Graph(bool oriented) {
  std::cin >> n_ >> m_;
  g_.resize(n_);
  for (int i = 0; i < m_; ++i) {
    int x, y;
    std::cin >> x >> y;
    g_[x - 1].push_back(y - 1);
    if (!oriented) {
      g_[y - 1].push_back(x - 1);
    }
  }
  color_.resize(n_, 0);
  component_.resize(n_, -1);
  topo_sort_.resize(0);
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

void Graph::Kosaraju() {
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
  std::cout << k - 1 << "\n";
  for (int v = 0; v < n_; ++v) {
    std::cout << component_[v] << " ";
  }
}
