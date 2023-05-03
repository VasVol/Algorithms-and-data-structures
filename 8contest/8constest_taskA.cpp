#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
  struct Edge {
    long long num;
    long long cost;
  };
  struct Vertex {
    long long num;
    long long dist;
    bool operator<(const Vertex& other) const {
      if (dist != other.dist) {
        return dist < other.dist;
      }
      return num < other.num;
    }
  };
  inline static const long long kInf = 2009000999;
  long long n_ = 0;
  long long m_ = 0;
  std::vector<std::vector<Edge>> g_;

 public:
  Graph(int n, int m, const std::vector<std::vector<int>>& g);
  std::vector<long long> Dijkstra(long long start);
};

int main() {
  long long cnt;
  std::cin >> cnt;
  for (long long k = 0; k < cnt; ++k) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(m, std::vector<int>(3));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < 3; ++j) {
        std::cin >> g[i][j];
      }
    }
    Graph gr(n, m, g);
    long long start;
    std::cin >> start;
    auto ans = gr.Dijkstra(start);
    for (auto dist : ans) {
      std::cout << dist << " ";
    }
  }
}

Graph::Graph(int n, int m, const std::vector<std::vector<int>>& g): n_(n), m_(m) {
  g_.resize(n_);
  for (long long i = 0; i < m_; ++i) {
    long long v1 = g[i][0];
    long long v2 = g[i][1];
    long long cost = g[i][2];
    g_[v1].push_back({v2, cost});
    g_[v2].push_back({v1, cost});
  }
}

std::vector<long long> Graph::Dijkstra(long long start) {
  std::vector<long long> min_dist_(n_, kInf);
  std::set<Vertex> not_used_;
  std::vector<bool> used_(n_, false);
  min_dist_[start] = 0;
  not_used_.insert({start, min_dist_[start]});
  while (!not_used_.empty()) {
    auto it = not_used_.begin();
    auto vert = *it;
    used_[vert.num] = true;
    not_used_.erase(it);
    for (auto edge : g_[vert.num]) {
      if (used_[edge.num]) {
        continue;
      }
      long long new_dist =
        std::min(min_dist_[edge.num], min_dist_[vert.num] + edge.cost);
      not_used_.erase({edge.num, min_dist_[edge.num]});
      min_dist_[edge.num] = new_dist;
      not_used_.insert({edge.num, min_dist_[edge.num]});
    }
  }
  return min_dist_;
}
