#include <iostream>
#include <vector>
using namespace std;

// Check if a queen can be placed at (row, col)
bool isSafe(const vector<int> &positions, int row, int col) {
  for (int prev = 0; prev < row; ++prev) {
    int prevCol = positions[prev];
    // same column or diagonal?
    if (prevCol == col || abs(prevCol - col) == abs(prev - row))
      return false;
  }
  return true;
}

// Backtracking utility
void solveNQ(int n, int row, vector<int> &positions,
	     vector<vector<int>> &solutions) {
  if (row == n) {
    solutions.push_back(positions);
    return;
  }
  for (int col = 0; col < n; ++col) {
    if (isSafe(positions, row, col)) {
      positions[row] = col;
      solveNQ(n, row + 1, positions, solutions);
    }
  }
}

int main(int argc, char *argv[]) {
  int n = 8;
  if (argc > 1)
    n = stoi(argv[1]);

  vector<int> positions(n);
  vector<vector<int>> solutions;
  solveNQ(n, 0, positions, solutions);

  cout << "Found " << solutions.size() << " solutions for " << n << "-Queens\n";
  // Print first solution as board
  if (!solutions.empty()) {
    auto &sol = solutions[0];
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c)
	cout << (sol[r] == c ? 'Q' : '.') << ' ';
      cout << '\n';
    }
  }
  return 0;
}
