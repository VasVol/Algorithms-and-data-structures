#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const double eps = 0.00001;

void bfs(int v, std::vector<bool>& used, const std::vector<std::vector<double>>& g,
         std::vector<int>& parent, const std::vector<std::vector<int>>& edges) {
  std::queue<int> q;
  q.push(v);
  used[v] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int to : edges[u]) {
      if ((g[u][to] > eps) && (!used[to])) {
        q.push(to);
        used[to] = true;
        parent[to] = u;
      }
    }
  }
}

double increase(int s, int t, std::vector<std::vector<double>>& g, const std::vector<int>& parent) {
  double min_cap = g[parent[t]][t];
  int curr = t;
  while (curr != s) {
    int v = parent[curr];
    min_cap = std::min(min_cap, g[v][curr]);
    curr = v;
  }
  curr = t;
  while (curr != s) {
    int v = parent[curr];
    g[v][curr] -= min_cap;
    g[curr][v] += min_cap;
    curr = v;
  }
  return min_cap;
}

double EdmondsKarp(int n, int s, int t, std::vector<std::vector<double>>& g,
                   const std::vector<std::vector<int>>& edges) {
  double ans = 0;
  std::vector<bool> used(n, false);
  std::vector<int> parent(n, -1);
  bfs(s, used, g, parent, edges);
  while (used[t]) {
    ans += increase(s, t, g, parent);
    used.assign(n, false);
    parent.assign(n, -1);
    bfs(s, used, g, parent, edges);
  }
  return ans;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  if (m == 0) {
    std::cout << "1\n1";
    return 0;
  }
  std::vector<std::vector<double>> gr(n + 2, std::vector<double>(n + 2, 0));
  std::vector<std::vector<int>> edges(n + 2);
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    gr[v][u] = 1.0;
    gr[u][v] = 1.0;
    ++gr[v][n + 1];
    ++gr[u][n + 1];
    edges[v].push_back(u);
    edges[u].push_back(v);
  }
  for (int v = 1; v <= n; ++v) {
    edges[0].push_back(v);
    edges[v].push_back(n + 1);
  }
  const int iter = 40;
  double l = 0, r = m;
  for (int it = 0; it < iter; ++it) {
    double sigma = (l + r) / 2;

    auto g = gr;
    for (int v = 1; v <= n; ++v) {
      g[0][v] = 2 * sigma;
    }

    if (EdmondsKarp(n + 2, 0, n + 1, g, edges) < 2 * m - eps) {
      l = sigma;
    } else {
      r = sigma;
    }
  }
  double ans = r - 1.0 / (2 * n * n);

  auto g = gr;
  for (int v = 1; v <= n; ++v) {
    g[0][v] = 2 * ans;
  }

  EdmondsKarp(n + 2, 0, n + 1, g, edges);
  std::vector<bool> used(n + 2, false);
  std::vector<int> parent(n + 2, -1);
  bfs(0, used, g, parent, edges);
  std::vector<int> vertices;
  for (int v = 1; v <= n; ++v) {
    if (!used[v]) {
      vertices.push_back(v);
    }
  }
  std::cout << vertices.size() << "\n";
  for (int v : vertices) {
    std::cout << v << "\n";
  }
}
