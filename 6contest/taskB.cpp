#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

std::vector<size_t> Increasing(int n, const std::vector<int>& new_sequence) {
  std::vector<int> sequence(n + 1);
  for (int i = 1; i <= n; ++i) {
    sequence[i] = new_sequence[i - 1];
  }
  std::vector<int> dp(n + 1, INT_MAX);
  dp[0] = -INT_MAX;
  std::vector<size_t> answers = {0};
  for (int i = 1; i <= n; ++i) {
    size_t idx =
        std::lower_bound(dp.begin(), dp.end(), sequence[i]) - dp.begin();
    answers.push_back(idx);
    dp[idx] = sequence[i];
  }
  auto iter = std::lower_bound(dp.begin(), dp.end(), INT_MAX);
  size_t ans;
  if ((iter == dp.end()) || (*iter == INT_MAX)) {
    ans = iter - 1 - dp.begin();
  } else {
    ans = iter - dp.begin();
  }
  size_t curr = ans;
  std::vector<size_t> answer;
  for (int i = n; i >= 1; --i) {
    if (answers[i] == curr) {
      answer.push_back(i);
      --curr;
    }
  }
  std::reverse(answer.begin(), answer.end());
  return answer;
}

struct ElemAndIdx {
  int elem;
  int idx;
};

bool operator<(ElemAndIdx a1, ElemAndIdx a2) {
  return (a1.elem < a2.elem) || (a1.elem == a2.elem && a1.idx < a2.idx);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<ElemAndIdx> sequence(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    sequence[i] = {x, 0};
  }
  std::reverse(sequence.begin(), sequence.end());
  for (int i = 0; i < n; ++i) {
    sequence[i].idx = i;
  }
  std::sort(sequence.begin(), sequence.end());
  std::vector<int> new_sequence(n);
  for (int i = 0; i < n; ++i) {
    new_sequence[sequence[i].idx] = i;
  }
  auto ans = Increasing(n, new_sequence);
  for (auto& x : ans) {
    x = n + 1 - x;
  }
  std::reverse(ans.begin(), ans.end());
  std::cout << ans.size() << "\n";
  for (auto x : ans) {
    std::cout << x << " ";
  }
}
