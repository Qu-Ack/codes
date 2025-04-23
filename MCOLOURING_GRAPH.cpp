#include <iostream>
#include <vector>
using namespace std;

#define V 4 // adjust as needed

// Utility to print color assignment
void printSolution(const vector<int> &color) {
  for (int v = 0; v < V; ++v)
    cout << color[v] << ' ';
  cout << '\n';
}

// Check if vertex v can be colored with color c
bool isSafe(int v, const vector<vector<bool>> &graph, const vector<int> &color,
	    int c) {
  for (int u = 0; u < V; ++u) {
    if (graph[v][u] && color[u] == c)
      return false;
  }
  return true;
}

// Backtracking utility
bool graphColoringUtil(const vector<vector<bool>> &graph, int m,
		       vector<int> &color, int v) {
  if (v == V)
    return true; // all vertices colored

  for (int c = 1; c <= m; ++c) {
    if (isSafe(v, graph, color, c)) {
      color[v] = c;
      if (graphColoringUtil(graph, m, color, v + 1))
	return true;
      color[v] = 0; // backtrack
    }
  }
  return false;
}

int main() {
  // Example graph (adjust adjacency matrix as needed)
  vector<vector<bool>> graph = {
      {0, 1, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 0}};
  int m = 3; // number of colors

  vector<int> color(V, 0);
  if (graphColoringUtil(graph, m, color, 0)) {
    cout << "Solution Exists: Following are the assigned colors:\n";
    printSolution(color);
  } else {
    cout << "No solution exists with " << m << " colors.\n";
  }
  return 0;
}
