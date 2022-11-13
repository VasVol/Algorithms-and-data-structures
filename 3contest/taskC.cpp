#include <iostream>
#include <vector>

struct Node {
  int val;
  int l;
  int r;
};

struct SegTree {
  std::vector<Node> tree;
  int size;
  int none = -(1 << 30);

  SegTree(std::vector<int>& a) {
    int sz = a.size();
    size = 1;
    while (size < sz) {
      size *= 2;
    }
    tree.resize(2 * size - 1);
    for (int i = 0; i < sz; ++i) {
      tree[size - 1 + i] = {a[i], i, i + 1};
    }
    for (int i = sz; i < size; ++i) {
      tree[size - 1 + i] = {none, i, i + 1};
    }
    for (int i = size - 2; i >= 0; --i) {
      Node son1 = tree[2 * i + 1];
      Node son2 = tree[2 * i + 2];
      tree[i] = {std::max(son1.val, son2.val), son1.l, son2.r};
    }
  }

  void Set(int i, int v, int x) {
    if (tree[x].r - tree[x].l == 1) {
      tree[x].val = v;
      return;
    }
    if (i < tree[2 * x + 1].r) {
      Set(i, v, 2 * x + 1);
    } else {
      Set(i, v, 2 * x + 2);
    }
    tree[x].val = std::max(tree[2 * x + 1].val, tree[2 * x + 2].val);
  }

  void Ans(int i, int v, int x, int& ans, bool& flag) {
    if (flag) {
      return;
    }
    if (tree[x].r <= i) {
      return;
    }
    if (tree[x].r - tree[x].l == 1) {
      if (tree[x].val >= v) {
        flag = true;
        ans = tree[x].l;
      }
      return;
    }
    if (tree[2 * x + 1].r <= i) {
      Ans(i, v, 2 * x + 2, ans, flag);
      return;
    }
    if (tree[2 * x + 1].val >= v) {
      Ans(i, v, 2 * x + 1, ans, flag);
    }
    if (tree[2 * x + 2].val >= v) {
      Ans(i, v, 2 * x + 2, ans, flag);
    }
  }
};

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
  SegTree st(a);
  for (int j = 0; j < m; ++j) {
    int c;
    std::cin >> c;
    if (c == 0) {
      int i, v;
      std::cin >> i >> v;
      --i;
      st.Set(i, v, 0);
    } else {
      int i, v;
      std::cin >> i >> v;
      --i;
      int ans = -2;
      bool flag = false;
      st.Ans(i, v, 0, ans, flag);
      std::cout << ans + 1 << "\n";
    }
  }
}
