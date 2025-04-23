#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int src, vector<vector<int>> &adj) {
  int V = adj.size();
  vector<bool> vis(V, false);
  vector<int> order;
  queue<int> q;

  vis[src] = true;
  q.push(src);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);
    for (int v : adj[u]) {
      if (!vis[v]) {
	vis[v] = true;
	q.push(v);
      }
    }
  }
  return order;
}

int main() {
  int V, E, src;
  cin >> V >> E >> src;
  vector<vector<int>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> traversal = bfs(src, adj);
  for (int u : traversal)
    cout << u << " ";
  return 0;
}
