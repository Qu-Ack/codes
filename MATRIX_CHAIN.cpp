#include <bits/stdc++.h>
using namespace std;

// Returns minimum number of scalar multiplications needed
// to multiply matrices A1..An with dimensions dims[0..n]
long matrixChainOrder(const vector<int> &dims) {
  int n = dims.size() - 1;
  // dp[i][j] = minimum cost to multiply Ai..Aj
  vector<vector<long>> dp(n + 2, vector<long>(n + 2, 0));

  // L is chain length
  for (int L = 2; L <= n; L++) {
    for (int i = 1; i <= n - L + 1; i++) {
      int j = i + L - 1;
      dp[i][j] = LONG_MAX;
      for (int k = i; k < j; k++) {
	long cost =
	    dp[i][k] + dp[k + 1][j] + (long)dims[i - 1] * dims[k] * dims[j];
	dp[i][j] = min(dp[i][j], cost);
      }
    }
  }
  return dp[1][n];
}

int main() {
  int n;
  cin >> n; // number of matrices
  vector<int> dims(n + 1);
  for (int i = 0; i <= n; i++) {
    cin >> dims[i]; // dimensions array of size n+1
  }
  cout << matrixChainOrder(dims) << "\n";
  return 0;
}
