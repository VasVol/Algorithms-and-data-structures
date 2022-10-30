#include <iostream>
#include <string>
#include <vector>

struct Element {
  int val;
  int idx;
  Element(int val = 0, int idx = 0) {
    this->val = val;
    this->idx = idx;
  }
};

struct MinMax {
  std::vector<Element> heap_min;
  std::vector<Element> heap_max;
  MinMax() {
    heap_min.resize(1);
    heap_max.resize(1);
  }
  void ExchangeHeapMin(int i, int j) {
    std::swap(heap_min[i], heap_min[j]);
    std::swap(heap_max[heap_min[i].idx].idx, heap_max[heap_min[j].idx].idx);
  }
  void ExchangeHeapMax(int i, int j) {
    std::swap(heap_max[i], heap_max[j]);
    std::swap(heap_min[heap_max[i].idx].idx, heap_min[heap_max[j].idx].idx);
  }
  void SiftUpHeapMin(int i) {
    while (i > 1 && heap_min[i / 2].val > heap_min[i].val) {
      ExchangeHeapMin(i, i / 2);
      i /= 2;
    }
  }
  void SiftUpHeapMax(int i) {
    while (i > 1 && heap_max[i / 2].val < heap_max[i].val) {
      ExchangeHeapMax(i, i / 2);
      i /= 2;
    }
  }
  void SiftDownHeapMin(int i) {
    while (2 * i <= (int)heap_min.size() - 1) {
      int u = 2 * i;
      if ((2 * i + 1 <= (int)heap_min.size() - 1) &&
          (heap_min[2 * i + 1].val < heap_min[u].val)) {
        u = 2 * i + 1;
      }
      if (heap_min[i].val > heap_min[u].val) {
        ExchangeHeapMin(i, u);
        i = u;
      } else {
        break;
      }
    }
  }
  void SiftDownHeapMax(int i) {
    while (2 * i <= (int)heap_max.size() - 1) {
      int u = 2 * i;
      if ((2 * i + 1 <= (int)heap_max.size() - 1) &&
          (heap_max[2 * i + 1].val > heap_max[u].val)) {
        u = 2 * i + 1;
      }
      if (heap_max[i].val < heap_max[u].val) {
        ExchangeHeapMax(i, u);
        i = u;
      } else {
        break;
      }
    }
  }
  void Insert(int x) {
    heap_min.push_back(Element(x, heap_min.size()));
    heap_max.push_back(Element(x, heap_max.size()));
    SiftUpHeapMin((int)heap_min.size() - 1);
    SiftUpHeapMax((int)heap_max.size() - 1);
  }
  int GetMin() { return heap_min[1].val; }
  int GetMax() { return heap_max[1].val; }
  void EraseHeapMin(int i) {
    ExchangeHeapMin(i, (int)heap_min.size() - 1);
    heap_min.pop_back();
    SiftUpHeapMin(i);
    SiftDownHeapMin(i);
  }
  void EraseHeapMax(int i) {
    ExchangeHeapMax(i, (int)heap_max.size() - 1);
    heap_max.pop_back();
    SiftUpHeapMax(i);
    SiftDownHeapMax(i);
  }
  void ExtractMin() {
    EraseHeapMax(heap_min[1].idx);
    EraseHeapMin(1);
  }
  void ExtractMax() {
    EraseHeapMin(heap_max[1].idx);
    EraseHeapMax(1);
  }
  int Size() { return (int)heap_min.size() - 1; }
  void Clear() {
    heap_min.resize(1);
    heap_max.resize(1);
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
