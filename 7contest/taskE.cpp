#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Graph {
 private:
  int n_ = 0;
  int m_ = 0;
  int timer_ = 0;
  std::vector<std::vector<int>> g_;
  std::vector<bool> used_;
  std::vector<int> tin_;
  std::vector<int> ret_;
  std::map<std::pair<int, int>, int> edge_number_;
  std::vector<int> parent_;
  std::vector<int> bridges_;
  std::set<std::pair<int, int>> multiple_edges_;

 public:
  Graph();
  void Dfs(int v);
  void FindBridges();
};

int main() {
  Graph gr;
  gr.FindBridges();
}

Graph::Graph() {
  std::cin >> n_ >> m_;
  g_.resize(n_);
  for (int i = 0; i < m_; ++i) {
    int x, y;
    std::cin >> x >> y;
    if (x == y) {
      continue;
    }
    --x, --y;
    if (edge_number_.find({x, y}) != edge_number_.end()) {
      multiple_edges_.insert({x, y});
      multiple_edges_.insert({y, x});
    } else {
      edge_number_[{x, y}] = i;
      edge_number_[{y, x}] = i;
      g_[x].push_back(y);
      g_[y].push_back(x);
    }
  }
  used_.resize(n_, false);
  tin_.resize(n_, -1);
  ret_.resize(n_, 1e9);
  parent_.resize(n_, -1);
  bridges_.resize(0);
}

void Graph::Dfs(int v) {
  tin_[v] = timer_++;
  ret_[v] = tin_[v];
  used_[v] = true;
  for (int u : g_[v]) {
    if (u == parent_[v]) {
      continue;
    }
    if (used_[u]) {
      ret_[v] = std::min(ret_[v], tin_[u]);
    } else {
      parent_[u] = v;
      Dfs(u);
      ret_[v] = std::min(ret_[v], ret_[u]);
      if ((ret_[u] == tin_[u]) &&
          (multiple_edges_.find({u, v}) == multiple_edges_.end())) {
        bridges_.push_back(edge_number_[{v, u}]);
      }
    }
  }
}

void Graph::FindBridges() {
  for (int v = 0; v < n_; ++v) {
    if (!used_[v]) {
      Dfs(v);
    }
  }
  std::sort(bridges_.begin(), bridges_.end());
  std::cout << bridges_.size() << "\n";
  for (int e : bridges_) {
    std::cout << e + 1 << " ";
  }
}
