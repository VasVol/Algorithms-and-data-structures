#include <iostream>
#include <string>

class Stack {
 private:
  struct Element {
    int value;
    int min;
    Element* prev;
    Element() : value(0), min(0), prev(nullptr) {}
  };
  Element head_;
  int len_;

 public:
  Stack() : len_(0) {}
  void Push(int x);
  void Pop();
  int Size() { return len_; }
  bool Empty() { return len_ == 0; }
  int Top() { return head_.prev->value; }
  int Min() { return head_.prev->min; }
  void Clear();
  ~Stack() { Clear(); }
};

class Queue {
 private:
  Stack st1_;
  Stack st2_;
  void Move();

 public:
  void Push(int x) { st1_.Push(x); }
  void Pop();
  int Min();
  int Size() { return st1_.Size() + st2_.Size(); }
  bool Empty() { return Size() == 0; }
  int Front();
  void Clear() {
    st1_.Clear();
    st2_.Clear();
  }
  ~Queue() { Clear(); }
};

void FrontWithErrorCheck(Queue& q, bool need_to_pop) {
  if (q.Empty()) {
    std::cout << "error\n";
  } else {
    std::cout << q.Front() << "\n";
    if (need_to_pop) {
      q.Pop();
    }
  }
}

void MinWithErrorCheck(Queue& q) {
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
      FrontWithErrorCheck(q, true);
    } else if (s == "front") {
      FrontWithErrorCheck(q, false);
    } else if (s == "size") {
      std::cout << q.Size() << "\n";
    } else if (s == "clear") {
      q.Clear();
      std::cout << "ok\n";
    } else if (s == "min") {
      MinWithErrorCheck(q);
    }
  }
  return 0;
}

void Stack::Push(int x) {
  ++len_;
  Element* elem = new Element;
  elem->value = x;
  elem->prev = head_.prev;
  head_.prev = elem;
  if (elem->prev == nullptr) {
    elem->min = x;
  } else {
    elem->min = std::min(x, elem->prev->min);
  }
}

void Stack::Clear() {
  while (len_ > 0) {
    Pop();
  }
}

void Stack::Pop() {
  --len_;
  Element* tmp = head_.prev;
  head_.prev = head_.prev->prev;
  delete tmp;
}

void Queue::Move() {
  while (st1_.Size() > 0) {
    st2_.Push(st1_.Top());
    st1_.Pop();
  }
}

int Queue::Front() {
  if (st2_.Empty()) {
    Move();
  }
  return st2_.Top();
}

void Queue::Pop() {
  if (st2_.Empty()) {
    Move();
  }
  st2_.Pop();
}

int Queue::Min() {
  if (st1_.Empty()) {
    return st2_.Min();
  }
  if (st2_.Empty()) {
    return st1_.Min();
  }
  return std::min(st1_.Min(), st2_.Min());
}
