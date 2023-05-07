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
  const long long kInf = 2009000999;
  long long n_ = 0;
  long long m_ = 0;
  std::vector<std::vector<Edge>> g_;
  std::vector<long long> min_dist_;
  std::set<Vertex> not_used_;
  std::vector<bool> used_;

 public:
  Graph();
  void Dijkstra(long long start);
};

int main() {
  long long cnt;
  std::cin >> cnt;
  for (long long i = 0; i < cnt; ++i) {
    Graph gr;
    long long start;
    std::cin >> start;
    gr.Dijkstra(start);
  }
}

Graph::Graph() {
  std::cin >> n_ >> m_;
  g_.resize(n_);
  min_dist_.resize(n_, kInf);
  used_.resize(n_, false);
  not_used_ = std::set<Vertex>();
  for (long long i = 0; i < m_; ++i) {
    long long v1;
    long long v2;
    long long cost;
    std::cin >> v1 >> v2 >> cost;
    g_[v1].push_back({v2, cost});
    g_[v2].push_back({v1, cost});
  }
}

void Graph::Dijkstra(long long start) {
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
  for (auto dist : min_dist_) {
    std::cout << dist << " ";
  }
}
