#include <iostream>
#include <string>
#include <vector>

class MinMax {
 private:
  struct Element {
    int val;
    int idx;
    Element(int val = 0, int idx = 0) : val(val), idx(idx) {}
  };
  std::vector<Element> heap_min_;
  std::vector<Element> heap_max_;
  void EraseHeapMin(int i);
  void EraseHeapMax(int i);
  void ExchangeHeapMin(int i, int j) {
    std::swap(heap_min_[i], heap_min_[j]);
    std::swap(heap_max_[heap_min_[i].idx].idx, heap_max_[heap_min_[j].idx].idx);
  }
  void ExchangeHeapMax(int i, int j) {
    std::swap(heap_max_[i], heap_max_[j]);
    std::swap(heap_min_[heap_max_[i].idx].idx, heap_min_[heap_max_[j].idx].idx);
  }
  void SiftUpHeapMin(int i) {
    while (i > 1 && heap_min_[i / 2].val > heap_min_[i].val) {
      ExchangeHeapMin(i, i / 2);
      i /= 2;
    }
  }
  void SiftUpHeapMax(int i) {
    while (i > 1 && heap_max_[i / 2].val < heap_max_[i].val) {
      ExchangeHeapMax(i, i / 2);
      i /= 2;
    }
  }
  void SiftDownHeapMin(int i);
  void SiftDownHeapMax(int i);

 public:
  MinMax() {
    heap_min_.resize(1);
    heap_max_.resize(1);
  }
  void Insert(int x);
  int GetMin() { return heap_min_[1].val; }
  int GetMax() { return heap_max_[1].val; }
  void ExtractMin() {
    EraseHeapMax(heap_min_[1].idx);
    EraseHeapMin(1);
  }
  void ExtractMax() {
    EraseHeapMin(heap_max_[1].idx);
    EraseHeapMax(1);
  }
  size_t Size() { return heap_min_.size() - 1; }
  void Clear() {
    heap_min_.resize(1);
    heap_max_.resize(1);
  }
};

int main() {
  MinMax a;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "clear") {
      a.Clear();
      std::cout << "ok\n";
    } else if (s == "size") {
      std::cout << a.Size() << "\n";
    } else if (s == "get_min") {
      if (a.Size() > 0) {
        std::cout << a.GetMin() << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "get_max") {
      if (a.Size() > 0) {
        std::cout << a.GetMax() << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "extract_min") {
      if (a.Size() > 0) {
        std::cout << a.GetMin() << "\n";
        a.ExtractMin();
      } else {
        std::cout << "error\n";
      }
    } else if (s == "extract_max") {
      if (a.Size() > 0) {
        std::cout << a.GetMax() << "\n";
        a.ExtractMax();
      } else {
        std::cout << "error\n";
      }
    } else if (s == "insert") {
      int x;
      std::cin >> x;
      a.Insert(x);
      std::cout << "ok\n";
    }
  }
}

void MinMax::SiftDownHeapMin(int i) {
  int sz = heap_min_.size();
  while (2 * i <= sz - 1) {
    int u = 2 * i;
    if ((2 * i + 1 <= sz - 1) &&
        (heap_min_[2 * i + 1].val < heap_min_[u].val)) {
      u = 2 * i + 1;
    }
    if (heap_min_[i].val > heap_min_[u].val) {
      ExchangeHeapMin(i, u);
      i = u;
    } else {
      break;
    }
  }
}

void MinMax::SiftDownHeapMax(int i) {
  int sz = heap_max_.size();
  while (2 * i <= sz - 1) {
    int u = 2 * i;
    if ((2 * i + 1 <= sz - 1) &&
        (heap_max_[2 * i + 1].val > heap_max_[u].val)) {
      u = 2 * i + 1;
    }
    if (heap_max_[i].val < heap_max_[u].val) {
      ExchangeHeapMax(i, u);
      i = u;
    } else {
      break;
    }
  }
}

void MinMax::Insert(int x) {
  heap_min_.push_back(Element(x, heap_min_.size()));
  heap_max_.push_back(Element(x, heap_max_.size()));
  SiftUpHeapMin(heap_min_.size() - 1);
  SiftUpHeapMax(heap_max_.size() - 1);
}

void MinMax::EraseHeapMin(int i) {
  ExchangeHeapMin(i, heap_min_.size() - 1);
  heap_min_.pop_back();
  SiftUpHeapMin(i);
  SiftDownHeapMin(i);
}

void MinMax::EraseHeapMax(int i) {
  ExchangeHeapMax(i, heap_max_.size() - 1);
  heap_max_.pop_back();
  SiftUpHeapMax(i);
  SiftDownHeapMax(i);
}
