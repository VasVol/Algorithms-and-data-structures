#include <cmath>
#include <iostream>
#include <vector>

class SegmentTree {
 private:
  struct Node {
    int val;
    int l;
    int r;
  };
  std::vector<Node> tree_;
  int size_;
  static const int kNone = -(1 << 30);
  void Set(int i, int v, int x);
  void Ans(int i, int v, int x, int& ans, bool& flag);

 public:
  SegmentTree(std::vector<int>& a);
  void Set(int i, int v);
  int Ans(int i, int v);
};

SegmentTree::SegmentTree(std::vector<int>& a) {
  int sz = a.size();
  size_ = pow(2, ceil(log2(sz)));
  tree_.resize(2 * size_ - 1);
  for (int i = 0; i < sz; ++i) {
    tree_[size_ - 1 + i] = {a[i], i, i + 1};
  }
  for (int i = sz; i < size_; ++i) {
    tree_[size_ - 1 + i] = {kNone, i, i + 1};
  }
  for (int i = size_ - 2; i >= 0; --i) {
    Node son1 = tree_[2 * i + 1];
    Node son2 = tree_[2 * i + 2];
    tree_[i] = {std::max(son1.val, son2.val), son1.l, son2.r};
  }
}

void SegmentTree::Set(int i, int v, int x) {
  if (tree_[x].r - tree_[x].l == 1) {
    tree_[x].val = v;
    return;
  }
  if (i < tree_[2 * x + 1].r) {
    Set(i, v, 2 * x + 1);
  } else {
    Set(i, v, 2 * x + 2);
  }
  tree_[x].val = std::max(tree_[2 * x + 1].val, tree_[2 * x + 2].val);
}

void SegmentTree::Set(int i, int v) { Set(i, v, 0); }

void SegmentTree::Ans(int i, int v, int x, int& ans, bool& flag) {
  if (flag) {
    return;
  }
  if (tree_[x].r <= i) {
    return;
  }
  if (tree_[x].r - tree_[x].l == 1) {
    if (tree_[x].val >= v) {
      flag = true;
      ans = tree_[x].l;
    }
    return;
  }
  if (tree_[2 * x + 1].r <= i) {
    Ans(i, v, 2 * x + 2, ans, flag);
    return;
  }
  if (tree_[2 * x + 1].val >= v) {
    Ans(i, v, 2 * x + 1, ans, flag);
  }
  if (tree_[2 * x + 2].val >= v) {
    Ans(i, v, 2 * x + 2, ans, flag);
  }
}

int SegmentTree::Ans(int i, int v) {
  int ans = -1;
  bool flag = false;
  Ans(i, v, 0, ans, flag);
  if (ans == -1) {
    return -1;
  }
  return ans + 1;
}

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Fast();
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  SegmentTree st(a);
  for (int j = 0; j < m; ++j) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int i, v;
      std::cin >> i >> v;
      --i;
      st.Set(i, v);
    } else {
      int i, v;
      std::cin >> i >> v;
      --i;
      std::cout << st.Ans(i, v) << "\n";
    }
  }
}
