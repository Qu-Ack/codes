#include <bits/stdc++.h>
using namespace std;

// 0/1 Knapsack using 2D DP
int knapsack01(int W, const vector<int> &wt, const vector<int> &val) {
  int n = wt.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int w = 0; w <= W; w++) {
      if (wt[i - 1] <= w) {
	dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wt[i - 1]] + val[i - 1]);
      } else {
	dp[i][w] = dp[i - 1][w];
      }
    }
  }
  return dp[n][W];
}

// Space-optimized 1D DP version
int knapsack01_opt(int W, const vector<int> &wt, const vector<int> &val) {
  vector<int> dp(W + 1, 0);
  int n = wt.size();
  for (int i = 0; i < n; i++) {
    for (int w = W; w >= wt[i]; w--) {
      dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    }
  }
  return dp[W];
}

int main() {
  int n, W;
  cin >> n >> W;
  vector<int> wt(n), val(n);
  for (int i = 0; i < n; i++)
    cin >> wt[i] >> val[i];
  cout << knapsack01(W, wt, val) << "\n";
  // Or use optimized:
  // cout << knapsack01_opt(W, wt, val) << "\n";
  return 0;
}
