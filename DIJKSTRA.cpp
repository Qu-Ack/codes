#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>; // (distance, vertex)

// Computes shortest distances from source to all vertices
vector<int> dijkstra(int V, vector<vector<pii>> &adj, int src) {
  const int INF = 1e9;
  vector<int> dist(V, INF);
  priority_queue<pii, vector<pii>, greater<pii>> pq;

  dist[src] = 0;
  pq.push({0, src}); // (distance, vertex)

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue; // stale entry

    for (auto &[w, v] : adj[u]) {
      if (dist[u] + w < dist[v]) {
	dist[v] = dist[u] + w;
	pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

int main() {
  int V, E, src;
  cin >> V >> E >> src;
  vector<vector<pii>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({w, v});
    adj[v].push_back({w, u}); // omit for directed graph
  }

  auto dist = dijkstra(V, adj, src);
  for (int i = 0; i < V; i++) {
    cout << "Distance to " << i << " = " << (dist[i] == 1e9 ? -1 : dist[i])
	 << "\n";
  }
  return 0;
}
