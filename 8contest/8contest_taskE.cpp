#include <algorithm>
#include <iostream>
#include <vector>

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Elem {
  int vertex;
  int cost;
};

void PrintAns(const std::vector<int>& ans, Elem elem) {
  std::vector<int> answer;
  answer.push_back(elem.vertex);
  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    answer.push_back(*it);
    if (*it == elem.vertex) {
      break;
    }
  }
  std::cout << answer.size() << "\n";
  for (int x : answer) {
    std::cout << x + 1 << " ";
  }
}

void FordBellman(int num, std::vector<std::vector<int>>& dp,
                 std::vector<std::vector<Elem>>& parent,
                 const std::vector<std::vector<int>>& costs) {
  const int kNoEdge = 1e5;
  for (int cost = 1; cost <= num; ++cost) {
    for (int vertex = 0; vertex < num; ++vertex) {
      dp[vertex][cost] = dp[vertex][cost - 1];
      parent[vertex][cost] = parent[vertex][cost - 1];
      for (int from = 0; from < num; ++from) {
        if (costs[from][vertex] == kNoEdge) {
          continue;
        }
        if (dp[from][cost - 1] + costs[from][vertex] < dp[vertex][cost]) {
          dp[vertex][cost] = dp[from][cost - 1] + costs[from][vertex];
          parent[vertex][cost] = {from, cost - 1};
        }
      }
    }
  }
}

void Solve(int num, const std::vector<std::vector<int>>& costs) {
  const int kInf = 1e9;
  std::vector<std::vector<int>> dp(num, std::vector<int>(num + 1, kInf));
  dp[0][0] = 0;
  std::vector<std::vector<Elem>> parent(num,
                                        std::vector<Elem>(num + 1, {-1, -1}));
  FordBellman(num, dp, parent, costs);
  int curr = -1;
  for (int vertex = 0; vertex < num; ++vertex) {
    if (dp[vertex][num] < dp[vertex][num - 1]) {
      curr = vertex;
      break;
    }
  }
  if (curr == -1) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  std::vector<int> ans;
  std::vector<bool> used(num, false);
  Elem elem = {curr, num};
  while (!used[elem.vertex]) {
    ans.push_back(elem.vertex);
    used[elem.vertex] = true;
    elem = parent[elem.vertex][elem.cost];
  }
  PrintAns(ans, elem);
}

int main() {
  Fast();
  int num;
  std::cin >> num;
  std::vector<std::vector<int>> costs(num, std::vector<int>(num));
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cin >> costs[i][j];
    }
  }
  Solve(num, costs);
}
