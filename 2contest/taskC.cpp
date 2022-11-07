#include <iostream>
#include <string>
#include <vector>

class HeapMin {
 private:
  std::vector<long long> v_;
  std::vector<int> num_;
  std::vector<int> ptr_;
  void Exchange(int i, int j);
  void SiftUp(int i);
  void SiftDown(int i);

 public:
  HeapMin();
  void Insert(int x, int idx);
  long long GetMin() {
    ptr_.push_back(0);
    return v_[1];
  }
  void ExtractMin();
  void DecreaseKey(int idx, long long d);
};

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  FastInputOutput();
  HeapMin a;
  int n;
  std::cin >> n;
  for (int j = 1; j <= n; ++j) {
    std::string s;
    std::cin >> s;
    if (s == "getMin") {
      std::cout << a.GetMin() << "\n";
    } else if (s == "extractMin") {
      a.ExtractMin();
    } else if (s == "insert") {
      int x;
      std::cin >> x;
      a.Insert(x, j);
    } else if (s == "decreaseKey") {
      int i, d;
      std::cin >> i >> d;
      a.DecreaseKey(i, d);
    }
  }
}

void HeapMin::Exchange(int i, int j) {
  std::swap(v_[i], v_[j]);
  std::swap(num_[i], num_[j]);
  std::swap(ptr_[num_[i]], ptr_[num_[j]]);
}

void HeapMin::SiftUp(int i) {
  while (i > 1 && v_[i / 2] > v_[i]) {
    Exchange(i, i / 2);
    i /= 2;
  }
}

void HeapMin::SiftDown(int i) {
  int sz = v_.size();
  while (2 * i <= sz - 1) {
    int u = 2 * i;
    if ((2 * i + 1 <= sz - 1) && (v_[2 * i + 1] < v_[u])) {
      u = 2 * i + 1;
    }
    if (v_[i] > v_[u]) {
      Exchange(i, u);
      i = u;
    } else {
      break;
    }
  }
}

void HeapMin::Insert(int x, int idx) {
  v_.push_back(x);
  num_.push_back(idx);
  ptr_.push_back(v_.size() - 1);
  SiftUp(v_.size() - 1);
}

void HeapMin::ExtractMin() {
  Exchange(1, v_.size() - 1);
  v_.pop_back();
  num_.pop_back();
  SiftDown(1);
  ptr_.push_back(0);
}

void HeapMin::DecreaseKey(int idx, long long d) {
  v_[ptr_[idx]] -= d;
  SiftUp(ptr_[idx]);
  ptr_.push_back(0);
}

HeapMin::HeapMin() {
  v_.resize(1);
  num_.resize(1);
  ptr_.resize(1);
}
