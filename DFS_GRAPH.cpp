#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<bool> &vis, vector<vector<int>> &adj) {
  vis[u] = true;	 // mark current node visited
  cout << u << " ";	 // process node (e.g., print)
  for (int v : adj[u]) { // for each neighbor
    if (!vis[v]) {
      dfs(v, vis, adj); // recurse
    }
  }
}

int main() {
  int V, E, src;
  cin >> V >> E >> src;
  vector<vector<int>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u); // omit for directed graphs
  }
  vector<bool> vis(V, false);
  dfs(src, vis, adj);
  return 0;
}
