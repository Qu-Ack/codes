#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int u, v, w;
};

// Returns true if no negative cycle; false otherwise.
// On success, dist[] holds shortest distances from src.
bool bellmanFord(int V, vector<Edge> &edges, int src, vector<long long> &dist) {
  const long long INF = LLONG_MAX / 4;
  dist.assign(V, INF);
  dist[src] = 0;

  // Relax edges V-1 times
  for (int i = 1; i < V; i++) {
    bool anyChange = false;
    for (auto &e : edges) {
      if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
	dist[e.v] = dist[e.u] + e.w;
	anyChange = true;
      }
    }
    if (!anyChange)
      break; // early exit if no update
  }

  // Check for negative-weight cycles
  for (auto &e : edges) {
    if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
      return false;
    }
  }
  return true;
}

int main() {
  int V, E, src;
  cin >> V >> E >> src;
  vector<Edge> edges(E);
  for (int i = 0; i < E; i++) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }

  vector<long long> dist;
  if (!bellmanFord(V, edges, src, dist)) {
    cout << "Negative weight cycle detected\n";
  } else {
    for (int i = 0; i < V; i++) {
      if (dist[i] == LLONG_MAX / 4)
	cout << "Vertex " << i << ": unreachable\n";
      else
	cout << "Vertex " << i << ": " << dist[i] << "\n";
    }
  }
  return 0;
}
