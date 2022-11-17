#include <iostream>
#include <vector>

const int kBlockSize = 5;

int SortSelect(std::vector<int>& v, int begin, int end, int k) {
  for (int i = begin; i < end; ++i) {
    for (int j = i; j >= begin + 1; --j) {
      if (v[j - 1] > v[j]) {
        std::swap(v[j - 1], v[j]);
      } else {
        break;
      }
    }
  }
  return v[begin + k];
}

void Partition(std::vector<int>& l, std::vector<int>& m, std::vector<int>& r,
               std::vector<int>& a, int pivot) {
  for (int x : a) {
    if (x < pivot) {
      l.push_back(x);
    } else if (x == pivot) {
      m.push_back(x);
    } else {
      r.push_back(x);
    }
  }
}
int QuickSelect(std::vector<int>& v, size_t k) {
  if (v.size() <= kBlockSize - 1) {
    return SortSelect(v, 0, v.size(), k);
  }
  std::vector<int> medians;
  for (size_t i = 0; i + kBlockSize - 1 < v.size(); i += kBlockSize) {
    medians.push_back(SortSelect(v, i, i + kBlockSize, kBlockSize / 2));
  }
  int pivot = QuickSelect(medians, medians.size() / 2);
  std::vector<int> l, m, r;
  Partition(l, m, r, v, pivot);
  if (k < l.size()) {
    return QuickSelect(l, k);
  }
  if (k + r.size() >= v.size()) {
    return QuickSelect(r, k - v.size() + r.size());
  }
  return pivot;
}

void Copy(std::vector<int>& from, std::vector<int>& to) {
  for (int x : from) {
    to.push_back(x);
  }
}

std::vector<int> QuickSort(std::vector<int>& a) {
  if (a.size() <= 1) {
    return a;
  }
  std::vector<int> b = a;
  int pivot = QuickSelect(b, b.size() / 2);
  std::vector<int> l, m, r;
  Partition(l, m, r, a, pivot);
  l = QuickSort(l);
  r = QuickSort(r);
  std::vector<int> ans;
  Copy(l, ans);
  Copy(m, ans);
  Copy(r, ans);
  return ans;
}

void Fast() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  Fast();
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  a = QuickSort(a);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }
  return 0;
}
