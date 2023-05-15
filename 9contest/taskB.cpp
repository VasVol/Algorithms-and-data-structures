#include <iostream>
#include <vector>
#include <algorithm>

// Disjoint Set Union
class DSU {
 private:
  std::vector<int> parent;
  std::vector<int> size;

 public:
  DSU(int n);
  int get(int v);
  void unite(int u, int v);
  bool same(int u, int v);
};

struct Edge {
  int u;
  int v;
  int c;
};

bool operator<(const Edge& a, const Edge& b) {
  if (a.c != b.c) {
    return a.c < b.c;
  }
  if (a.u != b.u) {
    return a.u < b.u;
  }
  return a.v < b.v;
}

void kruskal(int n, std::vector<Edge>& g) {
  std::sort(g.begin(), g.end());
  long long ans = 0;
  DSU dsu(n);
  for (Edge e : g) {
    if (!dsu.same(e.u, e.v)) {
      dsu.unite(e.u, e.v);
      ans += e.c;
    }
  }
  std::cout << ans;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> g(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> g[i].u >> g[i].v >> g[i].c;
    --g[i].u, --g[i].v;
  }
  kruskal(n, g);
}

int DSU::get(int v) {
  if (parent[v] == -1) {
    return v;
  }
  int x = get(parent[v]);
  parent[v] = x;
  return x;
}

void DSU::unite(int u, int v) {
  u = get(u);
  v = get(v);
  if (u == v) {
    return;
  }
  if (size[u] < size[v]) {
    std::swap(u, v);
  }
  parent[v] = u;
  size[u] += size[v];
}

bool DSU::same(int u, int v) {
  return get(u) == get(v);
}

DSU::DSU(int n): parent(n, -1), size(n, 1) {}
