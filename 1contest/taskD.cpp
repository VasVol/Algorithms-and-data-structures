#include <deque>
#include <iostream>

void Move(std::deque<int>& d1, std::deque<int>& d2) {
  if (d2.size() > d1.size()) {
    d1.push_back(d2.front());
    d2.pop_front();
  }
}

int main() {
  std::deque<int> d1, d2;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    if (c == '+') {
      int x;
      std::cin >> x;
      d2.push_back(x);
    } else if (c == '*') {
      int x;
      std::cin >> x;
      d2.push_front(x);
    } else if (c == '-') {
      std::cout << d1.front() << "\n";
      d1.pop_front();
    }
    Move(d1, d2);
  }
  return 0;
}
