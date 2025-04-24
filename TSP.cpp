#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

// Solve TSP with Held–Karp DP; returns minimal cost and fills `parent`
int tsp(int n, const vector<vector<int>> &cost, vector<vector<int>> &parent) {
  int N = 1 << n;
  // dp[mask][i]: min cost to visit set mask, end at i
  vector<vector<int>> dp(N, vector<int>(n, INF));
  parent.assign(N, vector<int>(n, -1));
  // Base: from city 0 to i
  dp[1 << 0][0] = 0;

  for (int mask = 1; mask < N; ++mask) {
    for (int u = 0; u < n; ++u) {
      if (!(mask & (1 << u)))
	continue;
      int prev_mask = mask ^ (1 << u);
      if (prev_mask == 0 && u == 0)
	continue;
      if (prev_mask == 0)
	continue;
      // try coming to u from v
      for (int v = 0; v < n; ++v) {
	if (!(prev_mask & (1 << v)))
	  continue;
	int val = dp[prev_mask][v] + cost[v][u];
	if (val < dp[mask][u]) {
	  dp[mask][u] = val;
	  parent[mask][u] = v;
	}
      }
    }
  }
  // close the tour returning to 0
  int best = INF, last = -1;
  int full = N - 1;
  for (int i = 1; i < n; ++i) {
    int val = dp[full][i] + cost[i][0];
    if (val < best) {
      best = val;
      last = i;
    }
  }
  parent[full][0] = last;
  return best;
}

// Reconstruct path from parent table
vector<int> getPath(int n, const vector<vector<int>> &parent) {
  int mask = (1 << n) - 1;
  vector<int> path;
  int cur = 0; // we set parent[full][0] = last
  while (true) {
    path.push_back(cur);
    int prev = parent[mask][cur];
    if (prev < 0)
      break;
    mask ^= (1 << cur);
    cur = prev;
  }
  reverse(path.begin(), path.end());
  return path;
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> cost(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> cost[i][j];

  vector<vector<int>> parent;
  int bestCost = tsp(n, cost, parent);

  auto tour = getPath(n, parent);
  cout << "Minimum cost: " << bestCost << "\nTour: ";
  for (int city : tour)
    cout << city << " ";
  cout << 0 << "\n"; // return to start
  return 0;
}
