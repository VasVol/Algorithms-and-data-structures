#include <iostream>
#include <vector>

class AVL {
 private:
  struct Node {
    long long val;
    int h = 1;
    std::vector<Node*> children{2, nullptr};
    Node* parent = nullptr;
    Node(long long val) : val(val) {}
  };
  Node* root_ = nullptr;
  void Connect(Node* node1, Node* node2, int i);
  int SonNumber(Node* node);
  void UpdateH(Node* node);
  int H(Node* node);
  int Delta(Node* node);
  void Spin(Node* node, int i);
  long long Next(long long x, Node* node);
  void Clear(Node* node);
  void Fix(Node* node);

 public:
  void Insert(long long x);
  long long Next(long long x);
  ~AVL();
};

void AVL::Connect(Node* node1, Node* node2, int i) {
  node1->children[i] = node2;
  if (node2 != nullptr) {
    node2->parent = node1;
  }
  UpdateH(node1);
  if (node2 == root_) {
    root_ = node1;
  }
}

int AVL::SonNumber(Node* node) {
  if (node->parent->children[0] == node) {
    return 0;
  }
  return 1;
}

void AVL::UpdateH(Node* node) {
  node->h = 1 + std::max(H(node->children[0]), H(node->children[1]));
}

int AVL::H(Node* node) { return node != nullptr ? node->h : 0; }

int AVL::Delta(Node* node) {
  return H(node->children[0]) - H(node->children[1]);
}

void AVL::Spin(Node* node, int i) {
  Node* parent = node->parent;
  Node* tmp = parent->parent;
  int j = 0;
  if (tmp != nullptr) {
    j = SonNumber(parent);
  }
  Connect(parent, node->children[1 - i], i);
  Connect(node, parent, 1 - i);
  if (tmp != nullptr) {
    Connect(tmp, node, j);
  }
}

long long AVL::Next(long long x, Node* node) {
  if (node == nullptr) {
    return -1;
  }
  if (node->val == x) {
    return x;
  }
  if (node->val < x) {
    return Next(x, node->children[1]);
  }
  int ans = Next(x, node->children[0]);
  if (ans != -1) {
    return ans;
  }
  return node->val;
}

void AVL::Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->children[0]);
  Clear(node->children[1]);
  delete node;
}

void AVL::Insert(long long x) {
  if (root_ == nullptr) {
    root_ = new Node(x);
    return;
  }
  Node* curr = root_;
  while (curr->val != x) {
    if (curr->val > x) {
      if (curr->children[0] == nullptr) {
        Node* new_node = new Node(x);
        Connect(curr, new_node, 0);
        Fix(new_node);
        return;
      }
      curr = curr->children[0];
    } else {
      if (curr->children[1] == nullptr) {
        Node* new_node = new Node(x);
        Connect(curr, new_node, 1);
        Fix(new_node);
        return;
      }
      curr = curr->children[1];
    }
  }
}

void AVL::Fix(Node* node) {
  UpdateH(node);
  if (node == root_) {
    root_->parent = nullptr;
    return;
  }
  UpdateH(node->parent);
  int i = SonNumber(node);
  if (Delta(node->parent) == 2 - 4 * i) {
    if (Delta(node) == 0 || Delta(node) == 1 - 2 * i) {
      Spin(node, i);
      Fix(node);
    } else {
      Node* child = node->children[1 - i];
      Spin(child, 1 - i);
      Spin(child, i);
      Fix(child);
    }
  } else {
    Fix(node->parent);
  }
}

long long AVL::Next(long long x) { return Next(x, root_); }

AVL::~AVL() { Clear(root_); }

int main() {
  AVL t;
  int n;
  std::cin >> n;
  long long prev = 0;
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    long long x;
    std::cin >> x;
    if (c == '+') {
      t.Insert((x + prev) % 1000'000'000);
      prev = 0;
    } else if (c == '?') {
      long long ans = t.Next(x);
      std::cout << ans << "\n";
      prev = ans;
    }
  }
}
