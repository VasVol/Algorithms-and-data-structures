#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(1.0, 10.0);

class Treap {
 private:
  struct Node {
    long long x;
    double y;
    int count = 1;
    Node* right = nullptr;
    Node* left = nullptr;
    Node(long long x, double y) : x(x), y(y) {}
  };
  Node* root_ = nullptr;
  static Node* Merge(Node* a, Node* b);
  static void Update(Node* node);
  static std::pair<Node*, Node*> Split(Node* node, long long k);
  static long long Next(long long x, Node* node);
  static long long Prev(long long x, Node* node);
  static long long Kth(int k, Node* node);

 public:
  void Insert(long long x);
  void Erase(long long x);
  bool Find(long long x);
  long long Next(long long x);
  long long Prev(long long x);
  long long Kth(int k);
  static void Clear(Node* curr);
  ~Treap();
};

int main() {
  Treap t;
  std::string s;
  long long x;
  while (std::cin >> s >> x) {
    if (s == "insert") {
      t.Insert(x);
    } else if (s == "delete") {
      t.Erase(x);
    } else if (s == "exists") {
      std::cout << (t.Find(x) ? "true" : "false") << "\n";
    } else if (s == "next") {
      long long ans = t.Next(x);
      std::cout << (ans != -1 ? std::to_string(ans) : "none") << "\n";
    } else if (s == "prev") {
      long long ans = t.Prev(x);
      std::cout << (ans != -1 ? std::to_string(ans) : "none") << "\n";
    } else if (s == "kth") {
      long long ans = t.Kth(x);
      std::cout << (ans != -1 ? std::to_string(ans) : "none") << "\n";
    }
  }
}

void Treap::Update(Node* node) {
  if (node != nullptr) {
    node->count = (node->left != nullptr ? node->left->count : 0) +
                  (node->right != nullptr ? node->right->count : 0) + 1;
  }
}

std::pair<Treap::Node*, Treap::Node*> Treap::Split(Node* node, long long k) {
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  if (node->x <= k) {
    std::pair p = Split(node->right, k);
    node->right = p.first;
    Update(node);
    return {node, p.second};
  }
  std::pair p = Split(node->left, k);
  node->left = p.second;
  Update(node);
  return {p.first, node};
}

Treap::Node* Treap::Merge(Node* a, Node* b) {
  if (a == nullptr) {
    return b;
  }
  if (b == nullptr) {
    return a;
  }
  if (a->y < b->y) {
    a->right = Merge(a->right, b);
    Update(a);
    return a;
  }
  b->left = Merge(a, b->left);
  Update(b);
  return b;
}

Treap::~Treap() { Clear(root_); }

long long Treap::Next(long long x) { return Next(x, root_); }

long long Treap::Kth(int k) { return Kth(k, root_); }

long long Treap::Kth(int k, Node* node) {
  if (node == nullptr || k < 0 || k >= node->count) {
    return -1;
  }
  int i = node->left != nullptr ? node->left->count : 0;
  if (i > k) {
    return Kth(k, node->left);
  }
  if (i == k) {
    return node->x;
  }
  return Kth(k - i - 1, node->right);
}

long long Treap::Prev(long long x) { return Prev(x, root_); }

long long Treap::Next(long long x, Node* node) {
  if (node == nullptr) {
    return -1;
  }
  if (node->x <= x) {
    return Next(x, node->right);
  }
  long long ans = Next(x, node->left);
  if (ans != -1) {
    return ans;
  }
  return node->x;
}

long long Treap::Prev(long long x, Node* node) {
  if (node == nullptr) {
    return -1;
  }
  if (node->x >= x) {
    return Prev(x, node->left);
  }
  long long ans = Prev(x, node->right);
  if (ans != -1) {
    return ans;
  }
  return node->x;
}

void Treap::Insert(long long x) {
  if (Find(x)) {
    return;
  }
  std::pair p = Split(root_, x);
  Node* new_element = new Node(x, dist(mt));
  if (root_ == nullptr) {
    root_ = new_element;
  } else {
    Node* tmp = Merge(p.first, new_element);
    root_ = Merge(tmp, p.second);
  }
  Update(root_);
}

void Treap::Erase(long long x) {
  if (!Find(x)) {
    return;
  }
  std::pair p = Split(root_, x);
  std::pair tmp = Split(p.first, x - 1);
  root_ = Merge(tmp.first, p.second);
  Update(root_);
  delete tmp.second;
}

bool Treap::Find(long long x) {
  Node* curr = root_;
  while (curr != nullptr) {
    if (curr->x == x) {
      return true;
    }
    if (curr->x > x) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return false;
}

void Treap::Clear(Node* curr) {
  if (curr != nullptr) {
    Clear(curr->left);
    Clear(curr->right);
    delete curr;
  }
}
