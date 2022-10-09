#include <iostream>
#include <string>

struct Element {
  int value;
  int min;
  Element* prev;
  Element() {
    value = 0;
    min = 0;
    prev = nullptr;
  }
};

struct Stack {
  Element head;
  int len;
  Stack() {
    len = 0;
    head = Element();
  }
  void Push(int x) {
    ++len;
    Element* elem = new Element;
    elem->value = x;
    elem->prev = head.prev;
    head.prev = elem;
    if (elem->prev == nullptr) {
      elem->min = x;
    } else {
      elem->min = std::min(x, elem->prev->min);
    }
  }
  void Pop() {
    --len;
    Element* tmp = head.prev;
    head.prev = head.prev->prev;
    delete tmp;
  }
  int Size() { return len; }
  bool Empty() { return len == 0; }
  int Top() { return head.prev->value; }
  int Min() { return head.prev->min; }
  void Clear() {
    while (len > 0) {
      Pop();
    }
  }
};

struct Queue {
  Stack st1;
  Stack st2;
  void Move() {
    while (st1.Size() > 0) {
      st2.Push(st1.Top());
      st1.Pop();
    }
  }
  void Push(int x) { st1.Push(x); }
  void Pop() {
    if (st2.Empty()) {
      Move();
    }
    st2.Pop();
  }
  int Min() {
    if (st1.Empty()) {
      return st2.Min();
    }
    if (st2.Empty()) {
      return st1.Min();
    }
    return std::min(st1.Min(), st2.Min());
  }
  int Size() { return st1.Size() + st2.Size(); }
  bool Empty() { return Size() == 0; }
  int Front() {
    if (st2.Empty()) {
      Move();
    }
    return st2.Top();
  }
  void Clear() {
    st1.Clear();
    st2.Clear();
  }
};

void Front1(Queue& q, bool need_to_pop) {
  if (q.Empty()) {
    std::cout << "error\n";
  } else {
    std::cout << q.Front() << "\n";
    if (need_to_pop) {
      q.Pop();
    }
  }
}

void Min1(Queue& q) {
  if (q.Empty()) {
    std::cout << "error\n";
  } else {
    std::cout << q.Min() << "\n";
  }
}

int main() {
  Queue q;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "enqueue") {
      int x;
      std::cin >> x;
      q.Push(x);
      std::cout << "ok\n";
    } else if (s == "dequeue") {
      Front1(q, true);
    } else if (s == "front") {
      Front1(q, false);
    } else if (s == "size") {
      std::cout << q.Size() << "\n";
    } else if (s == "clear") {
      q.Clear();
      std::cout << "ok\n";
    } else if (s == "min") {
      Min1(q);
    }
  }
  q.Clear();
  return 0;
}
