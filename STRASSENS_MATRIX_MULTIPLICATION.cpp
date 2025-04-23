#include <bits/stdc++.h>
using namespace std;

// Type alias for readability
using Matrix = vector<vector<int>>;

// Add or subtract two n×n matrices (sign = +1 for add, -1 for subtract)
Matrix add(const Matrix &A, const Matrix &B, int n, int sign = +1) {
  Matrix C(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] + sign * B[i][j];
  return C;
}

// Strassen's recursive multiplication
Matrix strassen(const Matrix &A, const Matrix &B) {
  int n = A.size();
  Matrix C(n, vector<int>(n));
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
    return C;
  }

  int m = n / 2;
  // Partition A and B into 4 submatrices each
  Matrix A11(m, vector<int>(m)), A12(m, vector<int>(m)), A21(m, vector<int>(m)),
      A22(m, vector<int>(m));
  Matrix B11(m, vector<int>(m)), B12(m, vector<int>(m)), B21(m, vector<int>(m)),
      B22(m, vector<int>(m));

  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + m];
      A21[i][j] = A[i + m][j];
      A22[i][j] = A[i + m][j + m];
      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + m];
      B21[i][j] = B[i + m][j];
      B22[i][j] = B[i + m][j + m];
    }

  // Compute the 7 products
  Matrix M1 = strassen(add(A11, A22, m), add(B11, B22, m));
  Matrix M2 = strassen(add(A21, A22, m), B11);
  Matrix M3 = strassen(A11, add(B12, B22, m, -1));
  Matrix M4 = strassen(A22, add(B21, B11, m, -1));
  Matrix M5 = strassen(add(A11, A12, m), B22);
  Matrix M6 = strassen(add(A21, A11, m, -1), add(B11, B12, m));
  Matrix M7 = strassen(add(A12, A22, m, -1), add(B21, B22, m));

  // Recombine into C
  Matrix C11 = add(add(M1, M4, m), add(M7, M5, m, -1), m);
  Matrix C12 = add(M3, M5, m);
  Matrix C21 = add(M2, M4, m);
  Matrix C22 = add(add(M1, M3, m), add(M6, M2, m, -1), m);

  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) {
      C[i][j] = C11[i][j];
      C[i][j + m] = C12[i][j];
      C[i + m][j] = C21[i][j];
      C[i + m][j + m] = C22[i][j];
    }
  return C;
}

int main() {
  int n;
  cin >> n; // n must be a power of 2
  Matrix A(n, vector<int>(n)), B(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> A[i][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> B[i][j];

  Matrix C = strassen(A, B);
  for (auto &row : C) {
    for (int x : row)
      cout << x << " ";
    cout << "\n";
  }
  return 0;
}
