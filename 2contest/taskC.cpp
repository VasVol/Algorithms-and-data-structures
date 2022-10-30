#include <iostream>
#include <string>
#include <vector>

struct HeapMin {
  std::vector<long long> v;
  std::vector<int> num;
  std::vector<int> ptr;
  HeapMin() {
    v.resize(1);
    num.resize(1);
    ptr.resize(1);
  }
  void Exchange(int i, int j) {
    std::swap(v[i], v[j]);
    std::swap(num[i], num[j]);
    std::swap(ptr[num[i]], ptr[num[j]]);
  }
  void SiftUp(int i) {
    while (i > 1 && v[i / 2] > v[i]) {
      Exchange(i, i / 2);
      i /= 2;
    }
  }
  void SiftDown(int i) {
    while (2 * i <= (int)v.size() - 1) {
      int u = 2 * i;
      if ((2 * i + 1 <= (int)v.size() - 1) && (v[2 * i + 1] < v[u])) {
        u = 2 * i + 1;
      }
      if (v[i] > v[u]) {
        Exchange(i, u);
        i = u;
      } else {
        break;
      }
    }
  }
  void Insert(int x, int idx) {
    v.push_back(x);
    num.push_back(idx);
    ptr.push_back((int)v.size() - 1);
    SiftUp((int)v.size() - 1);
  }
  long long GetMin() {
    ptr.push_back(0);
    return v[1];
  }
  void ExtractMin() {
    Exchange(1, (int)v.size() - 1);
    v.pop_back();
    num.pop_back();
    SiftDown(1);
    ptr.push_back(0);
  }
  void DecreaseKey(int idx, int d) {
    v[ptr[idx]] -= (long long)d;
    SiftUp(ptr[idx]);
    ptr.push_back(0);
  }
};

void FastInputOutput() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
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
