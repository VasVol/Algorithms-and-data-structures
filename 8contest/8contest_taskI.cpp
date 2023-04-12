#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

const int kN = 4;
const int kMaxSolution = 80;

struct Move {
  int dx;
  int dy;
  Move(int dx = 0, int dy = 0) : dx(dx), dy(dy) {}
  Move operator-() const {
    return Move(static_cast<int>(-dx), static_cast<int>(-dy));
  }
};

struct Matrix {
  size_t line = 0;
  int pos0x, pos0y;
  int func_val = 0;
  inline static std::map<size_t, int> func_g;
  Matrix(const std::vector<int>& input_vector) {
    for (int i = 0; i < kN; ++i) {
      for (int j = 0; j < kN; ++j) {
        Set(i, j, input_vector[i * kN + j]);
        if (Get(i, j) == 0) {
          pos0x = i;
          pos0y = j;
        }
      }
    }
  }
  int Get(int idx_i, int idx_j) const {
    int shift = kN * (kN * idx_i + idx_j);
    long long num = (1 << kN) - 1;
    return (line >> shift) & num;
  }
  void Set(int idx_i, int idx_j, size_t val) {
    int shift = kN * (kN * idx_i + idx_j);
    long long num = (1 << kN) - 1;
    line &= ~(num << shift);
    line |= (val << shift);
  }
  void Swap(int i1, int j1, int i2, int j2) {
    int tmp = Get(i1, j1);
    Set(i1, j1, Get(i2, j2));
    Set(i2, j2, tmp);
  }
  bool CanMove(Move move) const {
    int x = pos0x + move.dx;
    int y = pos0y + move.dy;
    return (0 <= x) && (x < kN) && (0 <= y) && (y < kN);
  }
  Matrix& Move(Move move) {
    int x = pos0x + move.dx;
    int y = pos0y + move.dy;
    Swap(pos0x, pos0y, x, y);
    pos0x = x;
    pos0y = y;
    return *this;
  }
};

bool operator<(const Matrix& m1, const Matrix& m2) {
  for (int i = 0; i < kN; ++i) {
    for (int j = 0; j < kN; ++j) {
      if (m1.Get(i, j) != m2.Get(i, j)) {
        return m1.Get(i, j) < m2.Get(i, j);
      }
    }
  }
  return false;
}

int ManhattanHeuristic(const Matrix& matrix) {
  int summ = 0;
  for (int i = 0; i < kN; ++i) {
    for (int j = 0; j < kN; ++j) {
      int elem = matrix.Get(i, j);
      if (elem != 0) {
        summ += std::abs(i - (elem - 1) / kN) + std::abs(j - (elem - 1) % kN);
      }
    }
  }
  return summ;
}

int LinearConflictHeuristic(const Matrix& matrix) {
  int summ = 0;
  for (int i = 0; i < kN; ++i) {
    for (int j = 0; j < kN; ++j) {
      int elem1 = matrix.Get(i, j);
      int elem2 = matrix.Get(i, j - 1);
      if ((j > 0) && ((elem1 - 1) / kN == i) && ((elem2 - 1) / kN == i) &&
          (elem2 > elem1) && (elem1 != 0) && (elem2 != 0)) {
        summ += 2;
      }
      elem2 = matrix.Get(i - 1, j);
      if ((i > 0) && ((elem1 - 1) % kN == j) && ((elem2 - 1) % kN == j) &&
          (elem2 > elem1) && (elem1 != 0) && (elem2 != 0)) {
        summ += 2;
      }
    }
  }
  return summ;
}

int FuncH(const Matrix& matrix) {
  return ManhattanHeuristic(matrix) + LinearConflictHeuristic(matrix);
}

bool Comp(const Matrix& m1, const Matrix& m2) {
  if (m1.func_val != m2.func_val) {
    return m1.func_val < m2.func_val;
  }
  return m1 < m2;
}

bool Solvable(const std::vector<int>& v_in) {
  int summ = 0;
  int sz = v_in.size();
  for (int i = 0; i < sz; ++i) {
    for (int j = i + 1; j < sz; ++j) {
      if ((v_in[j] < v_in[i]) && (v_in[j] != 0) && (v_in[i] != 0)) {
        summ += 1;
      }
    }
  }
  if (kN % 2 == 0) {
    for (int i = 0; i < sz; ++i) {
      if (v_in[i] == 0) {
        summ += i / kN + 1;
      }
    }
  }
  return (summ % 2) == 0;
}

char Direction(int dx, int dy) {
  if (dx == 0 && dy == 1) {
    return 'R';
  }
  if (dx == 0 && dy == -1) {
    return 'L';
  }
  if (dx == 1 && dy == 0) {
    return 'D';
  }
  return 'U';
}

void Solve(const std::vector<int>& start_vector,
           const std::vector<int>& finish_vector) {
  std::vector<Move> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  Matrix start(start_vector);
  Matrix finish(finish_vector);
  if (!Solvable(start_vector)) {
    std::cout << -1;
    return;
  }
  std::map<size_t, Move> parent;
  Matrix::func_g[start.line] = 0;
  std::set<Matrix, decltype(Comp)*> unused(Comp);
  unused.insert(start);
  while (!unused.empty()) {
    Matrix matr = *unused.begin();
    unused.erase(unused.begin());
    if (matr.line == finish.line) {
      break;
    }
    for (Move move : moves) {
      if (!matr.CanMove(move)) {
        continue;
      }
      if (Matrix::func_g[matr.line] + FuncH(matr) > kMaxSolution) {
        continue;
      }
      Matrix to = matr;
      to.Move(move);
      int cost = Matrix::func_g[matr.line] + 1;
      bool in_map = (Matrix::func_g.find(to.line) != Matrix::func_g.end());
      if ((!in_map) || (cost < Matrix::func_g[to.line])) {
        if (in_map) {
          to.func_val = Matrix::func_g[to.line] + FuncH(to);
          unused.erase(to);
        }
        Matrix::func_g[to.line] = cost;
        to.func_val = cost + FuncH(to);
        unused.insert(to);
        parent[to.line] = -move;
      }
    }
  }
  if (Matrix::func_g.find(finish.line) != Matrix::func_g.end()) {
    size_t ans = Matrix::func_g[finish.line];
    std::cout << ans << "\n";
    std::string str;
    Matrix curr = finish;
    while (str.size() < ans) {
      Move new_move = parent[curr.line];
      str += Direction(new_move.dx, new_move.dy);
      curr.Move(new_move);
    }
    std::reverse(str.begin(), str.end());
    std::cout << str << "\n";
  }
}

int main() {
  std::vector<int> start_vector(kN * kN);
  for (int i = 0; i < kN * kN; ++i) {
    std::cin >> start_vector[i];
  }
  std::vector<int> finish_vector(kN * kN, 0);
  for (int i = 0; i < kN * kN - 1; ++i) {
    finish_vector[i] = i + 1;
  }
  Solve(start_vector, finish_vector);
}
