#include <iostream>
#include <random>
#include <vector>

class HashTable {
 private:
  const long long kP = 1e18 + 9;
  const long long kP1 = 1e9 + 9;
  long long a_, b_;
  long long m_, cnt_;
  std::vector<std::vector<long long>> table_;
  long long Hash(long long x);
  void Resize();

 public:
  HashTable() : a_(1), b_(1), m_(1), cnt_(0), table_(1) {
    srand(time(nullptr) + 5);
  }
  bool Find(long long x);
  void Insert(long long x);
  void Erase(long long x);
  long long Size();
};

long long HashTable::Hash(long long x) {
  return (((a_ * x + b_) % kP) % m_ + m_) % m_;
}

bool HashTable::Find(long long x) {
  long long i = Hash(x);
  for (long long y : table_[i]) {
    if (y == x) {
      return true;
    }
  }
  return false;
}

void HashTable::Insert(long long x) {
  if (cnt_ >= m_) {
    Resize();
  }
  if (!Find(x)) {
    table_[Hash(x)].push_back(x);
    ++cnt_;
  }
}

void HashTable::Erase(long long x) {
  long long i = Hash(x);
  for (size_t j = 0; j < table_[i].size(); ++j) {
    if (table_[i][j] == x) {
      table_[i].erase(table_[i].begin() + j);
      --cnt_;
      return;
    }
  }
}

void HashTable::Resize() {
  m_ *= 2;
  a_ = random() % kP1;
  b_ = random() % kP1;
  std::vector<std::vector<long long>> tmp(m_);
  for (std::vector<long long> v : table_) {
    for (int x : v) {
      tmp[Hash(x)].push_back(x);
    }
  }
  table_ = tmp;
}

long long HashTable::Size() { return cnt_; }

int main() {
  HashTable h;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    int x;
    std::cin >> x;
    if (c == '+') {
      h.Insert(x);
    } else if (c == '-') {
      h.Erase(x);
    } else if (c == '?') {
      if (h.Find(x)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
}
