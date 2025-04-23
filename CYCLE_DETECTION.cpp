#include <bits/stdc++.h>
using namespace std;

// Recursive DFS to detect cycle in directed graph
bool dfsCycle(int u, const vector<vector<int>> &adj, vector<bool> &visited,
	      vector<bool> &recStack) {
  visited[u] = true;
  recStack[u] = true;

  for (int v : adj[u]) {
    if (!visited[v]) {
      if (dfsCycle(v, adj, visited, recStack))
	return true;
    } else if (recStack[v]) {
      // Found back-edge u->v
      return true;
    }
  }

  recStack[u] = false; // backtrack
  return false;
}

bool hasCycle(int V, const vector<vector<int>> &adj) {
  vector<bool> visited(V, false), recStack(V, false);
  for (int u = 0; u < V; ++u) {
    if (!visited[u]) {
      if (dfsCycle(u, adj, visited, recStack))
	return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;
  vector<vector<int>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v; // edge u -> v
    adj[u].push_back(v);
  }

  cout << (hasCycle(V, adj) ? "Cycle detected\n" : "No cycle\n");
  return 0;
}
