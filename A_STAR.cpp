#include <bits/stdc++.h>
using namespace std;
struct Node {
  int v;
  int g, f; // g = cost so far, f = g + h
  bool operator<(Node const &o) const {
    return f > o.f; // min-heap on f
  }
};

// Example heuristic: zero (makes A* = Dijkstra). Replace with problem-specific
// h(u,v).
int heuristic(int u, int goal) { return 0; }

// Returns cost of shortest path from src to goal, or -1 if unreachable
int aStar(int V, vector<vector<pair<int, int>>> &adj, int src, int goal) {
  const int INF = 1e9;
  vector<int> gscore(V, INF), fscore(V, INF);
  priority_queue<Node> open;
  vector<bool> closed(V, false);

  gscore[src] = 0;
  fscore[src] = heuristic(src, goal);
  open.push({src, 0, fscore[src]});

  while (!open.empty()) {
    auto [u, gu, fu] = open.top();
    open.pop();
    if (u == goal)
      return gu;
    if (closed[u])
      continue;
    closed[u] = true;

    for (auto &[w, v] : adj[u]) {
      int tentative_g = gu + w;
      if (tentative_g < gscore[v]) {
	gscore[v] = tentative_g;
	fscore[v] = tentative_g + heuristic(v, goal);
	open.push({v, gscore[v], fscore[v]});
      }
    }
  }
  return -1; // goal not reachable
}

int main() {
  int V, E, src, goal;
  cin >> V >> E >> src >> goal;
  vector<vector<pair<int, int>>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({w, v});
    adj[v].push_back({w, u});
  }
  int cost = aStar(V, adj, src, goal);
  if (cost < 0)
    cout << "Unreachable\n";
  else
    cout << "Shortest path cost = " << cost << "\n";
  return 0;
}
