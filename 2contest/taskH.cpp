#include <iostream>
#include <vector>

using namespace std;

int SortSelect(std::vector<int>& v, int k) {
  for (int i = 1; i < (int)v.size(); ++i) {
    for (int j = i; j >= 1; --j) {
      if (v[j - 1] > v[j]) {
        std::swap(v[j - 1], v[j]);
      } else {
        break;
      }
    }
  }
  return v[k];
}

int QuickSelect(std::vector<int>& v, int k) {
  int p = 10;
  if ((int)v.size() <= p - 1) {
    return SortSelect(v, k);
  }
  std::vector<int> medians;
  for (int i = 0; i + p - 1 < (int)v.size(); i += p) {
    auto a = std::vector<int>(v.begin() + i, v.begin() + i + p);
    medians.push_back(SortSelect(a, a.size() / 2));
  }
  int x = QuickSelect(medians, medians.size() / 2);
  std::vector<int> a, b;
  for (int elem : v) {
    if (elem < x) {
      a.push_back(elem);
    } else if (elem > x) {
      b.push_back(elem);
    }
  }
  if (k < (int)a.size()) {
    return QuickSelect(a, k);
  }
  if (k >= (int)v.size() - (int)b.size()) {
    return QuickSelect(b, k - v.size() + b.size());
  }
  return x;
}

bool Sorted(int begin, int end, vector<int> a) {
  for (int i = begin; i < end; ++i) {
    if (a[i - 1] > a[i]) {
      return false;
    }
  }
  return true;
}

std::vector<int> QuickSort(vector<int>& a) {
  if (a.size() <= 1) {
    return a;
  }
  std::vector<int> b = a;
  int p = QuickSelect(b, b.size() / 2);
  std::vector<int> l, m, r;
  for (int x : a) {
    if (x < p) {
      l.push_back(x);
    } else if (x == p) {
      m.push_back(x);
    } else {
      r.push_back(x);
    }
  }
  l = QuickSort(l);
  r = QuickSort(r);
  vector<int> ans;
  for (int x : l) {
    ans.push_back(x);
  }
  for (int x : m) {
    ans.push_back(x);
  }
  for (int x : r) {
    ans.push_back(x);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
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
