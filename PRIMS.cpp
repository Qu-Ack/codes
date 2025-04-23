#include <bits/stdc++.h>
using namespace std;
using Edge = pair<int, int>; // (weight, to)

// Returns total weight of MST
int primMST(int V, vector<vector<Edge>> &adj) {
  vector<bool> inMST(V, false);
  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
  int start = 0, mstWeight = 0;

  // (weight, vertex)
  pq.push({0, start});

  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    if (inMST[u])
      continue;
    inMST[u] = true;
    mstWeight += w;

    for (auto &[wt, v] : adj[u]) {
      if (!inMST[v]) {
	pq.push({wt, v});
      }
    }
  }
  return mstWeight;
}

int main() {
  int V, E;
  cin >> V >> E;
  vector<vector<Edge>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({w, v});
    adj[v].push_back({w, u});
  }
  cout << primMST(V, adj) << "\n";
  return 0;
}
