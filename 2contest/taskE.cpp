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
  std::vector<std::vector<Element>> heaps_;
  bool Cmp(int x, int y, int f);
  void Erase(int i, int f);
  void Exchange(int i, int j, int f);
  void SiftUp(int i, int f);
  void SiftDown(int i, int f);

 public:
  MinMax();
  void Insert(int x);
  int Get(int f);
  void Extract(int f);
  size_t Size();
  void Clear();
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
        std::cout << a.Get(0) << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "get_max") {
      if (a.Size() > 0) {
        std::cout << a.Get(1) << "\n";
      } else {
        std::cout << "error\n";
      }
    } else if (s == "extract_min") {
      if (a.Size() > 0) {
        std::cout << a.Get(0) << "\n";
        a.Extract(0);
      } else {
        std::cout << "error\n";
      }
    } else if (s == "extract_max") {
      if (a.Size() > 0) {
        std::cout << a.Get(1) << "\n";
        a.Extract(1);
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

void MinMax::SiftDown(int i, int f) {
  int sz = heaps_[f].size();
  while (2 * i <= sz - 1) {
    int u = 2 * i;
    if ((2 * i + 1 <= sz - 1) &&
        Cmp(heaps_[f][2 * i + 1].val, heaps_[f][u].val, f)) {
      u = 2 * i + 1;
    }
    if (Cmp(heaps_[f][i].val, heaps_[f][u].val, 1 - f)) {
      Exchange(i, u, f);
      i = u;
    } else {
      break;
    }
  }
}

void MinMax::Insert(int x) {
  heaps_[0].push_back(Element(x, heaps_[0].size()));
  heaps_[1].push_back(Element(x, heaps_[1].size()));
  SiftUp(heaps_[0].size() - 1, 0);
  SiftUp(heaps_[1].size() - 1, 1);
}

void MinMax::Erase(int i, int f) {
  Exchange(i, heaps_[f].size() - 1, f);
  heaps_[f].pop_back();
  SiftUp(i, f);
  SiftDown(i, f);
}

void MinMax::SiftUp(int i, int f) {
  while (i > 1 && Cmp(heaps_[f][i / 2].val, heaps_[f][i].val, 1 - f)) {
    Exchange(i, i / 2, f);
    i /= 2;
  }
}

void MinMax::Exchange(int i, int j, int f) {
  std::swap(heaps_[f][i], heaps_[f][j]);
  std::swap(heaps_[1 - f][heaps_[f][i].idx].idx,
            heaps_[1 - f][heaps_[f][j].idx].idx);
}

bool MinMax::Cmp(int x, int y, int f) {
  return ((f == 0) && (x < y)) || ((f == 1) && (x > y));
}

MinMax::MinMax() {
  heaps_.resize(2);
  heaps_[0].resize(1);
  heaps_[1].resize(1);
}

int MinMax::Get(int f) { return heaps_[f][1].val; }

void MinMax::Extract(int f) {
  Erase(heaps_[f][1].idx, 1 - f);
  Erase(1, f);
}

size_t MinMax::Size() { return heaps_[0].size() - 1; }

void MinMax::Clear() {
  heaps_[0].resize(1);
  heaps_[1].resize(1);
}
