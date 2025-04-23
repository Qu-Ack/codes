#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int u, v, w;
};
struct DSU {
  vector<int> p, r;
  DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
  int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;
    if (r[a] < r[b])
      swap(a, b);
    p[b] = a;
    if (r[a] == r[b])
      r[a]++;
    return true;
  }
};

int kruskalMST(int V, vector<Edge> &edges) {
  sort(edges.begin(), edges.end(),
       [](auto &a, auto &b) { return a.w < b.w; }); // O(E log E)
  DSU dsu(V);
  int mstWeight = 0, count = 0;
  for (auto &e : edges) {
    if (dsu.unite(e.u, e.v)) {
      mstWeight += e.w;
      if (++count == V - 1)
	break;
    }
  }
  return mstWeight;
}

int main() {
  int V, E;
  cin >> V >> E;
  vector<Edge> edges(E);
  for (int i = 0; i < E; i++)
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
  cout << kruskalMST(V, edges) << "\n";
  return 0;
}
