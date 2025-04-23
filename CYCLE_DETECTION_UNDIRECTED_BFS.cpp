#include <bits/stdc++.h>
using namespace std;

// Function to perform BFS from node start
bool bfs(int start, vector<vector<int>> &adj, vector<bool> &visited) {
  queue<pair<int, int>> q;
  q.push({start, -1});
  visited[start] = true;

  while (!q.empty()) {
    int node = q.front().first;
    int parent = q.front().second;
    q.pop();

    for (int neighbor : adj[node]) {

      if (!visited[neighbor]) {
	visited[neighbor] = true;
	q.push({neighbor, node});
      } else if (neighbor != parent) {
	return true;
      }
    }
  }
  return false;
}

vector<vector<int>> constructadj(int V, vector<vector<int>> &edges) {

  vector<vector<int>> adj(V);
  for (auto it : edges) {
    adj[it[0]].push_back(it[1]);
    adj[it[1]].push_back(it[0]);
  }

  return adj;
}

bool isCycle(int V, vector<vector<int>> &edges) {

  vector<vector<int>> adj = constructadj(V, edges);
  vector<bool> visited(V, false);

  for (int i = 0; i < V; i++) {

    if (!visited[i]) {
      if (bfs(i, adj, visited)) {
	return true;
      }
    }
  }

  // If no cycle is found
  return false;
}

int main() {
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {3, 4}};
  int V = 5;

  isCycle(V, edges) ? cout << "true" : cout << "false";

  return 0;
}
