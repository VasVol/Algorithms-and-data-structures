#include <iostream>
#include <string>
#include <vector>

class SplayTree {
 private:
  struct Node {
    std::pair<std::string, std::string> val;
    std::vector<Node*> children{2, nullptr};
    Node* parent = nullptr;
    Node(const std::pair<std::string, std::string>& x) : val(x) {}
  };
  Node* root_ = nullptr;
  void Connect(Node* node1, Node* node2, int i);
  int SonNumber(Node* node);
  void Spin(Node* node, int i);
  void Clear(Node* node);
  void Splay(Node* node);

 public:
  void Insert(const std::pair<std::string, std::string>& x);
  std::string Find(const std::string& s);
  ~SplayTree();
};

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Fast();
  SplayTree t;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    t.Insert({s1, s2});
    t.Insert({s2, s1});
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    std::cout << t.Find(s) << "\n";
  }
}

int SplayTree::SonNumber(Node* node) {
  if (node->parent->children[0] == node) {
    return 0;
  }
  return 1;
}

void SplayTree::Connect(Node* node1, Node* node2, int i) {
  node1->children[i] = node2;
  if (node2 != nullptr) {
    node2->parent = node1;
  }
  if (node2 == root_) {
    root_ = node1;
    root_->parent = nullptr;
  }
}

void SplayTree::Spin(Node* node, int i) {
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

void SplayTree::Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->children[0]);
  Clear(node->children[1]);
  delete node;
}

void SplayTree::Splay(SplayTree::Node* node) {
  if (node == root_) {
    return;
  }
  int i = SonNumber(node);
  if (node->parent == root_) {
    Spin(node, i);
    return;
  }
  int j = SonNumber(node->parent);
  if (i == j) {
    Spin(node->parent, j);
    Spin(node, i);
  } else {
    Spin(node, i);
    Spin(node, j);
  }
  Splay(node);
}

void SplayTree::Insert(const std::pair<std::string, std::string>& x) {
  if (root_ == nullptr) {
    root_ = new Node(x);
    return;
  }
  Node* curr = root_;
  while (curr->val.first != x.first) {
    if (curr->val.first > x.first) {
      if (curr->children[0] == nullptr) {
        Node* new_node = new Node(x);
        Connect(curr, new_node, 0);
        Splay(new_node);
        return;
      }
      curr = curr->children[0];
    } else {
      if (curr->children[1] == nullptr) {
        Node* new_node = new Node(x);
        Connect(curr, new_node, 1);
        Splay(new_node);
        return;
      }
      curr = curr->children[1];
    }
  }
}

std::string SplayTree::Find(const std::string& s) {
  Node* curr = root_;
  while (true) {
    if (curr == nullptr) {
      return "";
    }
    if (curr->val.first == s) {
      Splay(curr);
      return root_->val.second;
    }
    if (curr->val.first > s) {
      curr = curr->children[0];
    } else {
      curr = curr->children[1];
    }
  }
}

SplayTree::~SplayTree() { Clear(root_); }
