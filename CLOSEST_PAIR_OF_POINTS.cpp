#include <bits/stdc++.h>
using namespace std;

// Point structure
struct Point {
  int x, y, id;
};

// Compare by x, then y
struct cmpX {
  bool operator()(Point const &a, Point const &b) const {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  }
};
// Compare by y
struct cmpY {
  bool operator()(Point const &a, Point const &b) const { return a.y < b.y; }
};

double bestDist;
pair<int, int> bestPair;
vector<Point> pts, buffer;

// Update global best distance/pair
void updateAnswer(Point const &a, Point const &b) {
  double dx = double(a.x) - b.x;
  double dy = double(a.y) - b.y;
  double d = sqrt(dx * dx + dy * dy);
  if (d < bestDist) {
    bestDist = d;
    bestPair = {a.id, b.id};
  }
}

// Recursive divide-and-conquer on pts[l..r)
void solve(int l, int r) {
  int n = r - l;
  if (n <= 3) {
    // Brute-force base case
    for (int i = l; i < r; ++i)
      for (int j = i + 1; j < r; ++j)
	updateAnswer(pts[i], pts[j]);
    // Sort by y for merge step
    sort(pts.begin() + l, pts.begin() + r, cmpY());
    return;
  }
  int m = (l + r) / 2;
  int midX = pts[m].x;
  // Solve left and right
  solve(l, m);
  solve(m, r);
  // Merge by y-coordinate
  merge(pts.begin() + l, pts.begin() + m, pts.begin() + m, pts.begin() + r,
	buffer.begin(), cmpY());
  copy(buffer.begin(), buffer.begin() + n, pts.begin() + l);

  // Build strip in buffer
  int sz = 0;
  for (int i = l; i < r; ++i) {
    if (abs(pts[i].x - midX) < bestDist) {
      // Compare to previous points in strip
      for (int j = sz - 1; j >= 0 && double(pts[i].y) - buffer[j].y < bestDist;
	   --j) {
	updateAnswer(pts[i], buffer[j]);
      }
      buffer[sz++] = pts[i];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n; // Number of points
  pts.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
    pts[i].id = i;
  }

  // Prepare for recursion
  sort(pts.begin(), pts.end(),
       cmpX()); // Pre-sort by x :contentReference[oaicite:7]{index=7}
  buffer.resize(n);
  bestDist = 1e20;

  solve(0, n);

  // Output result
  cout << fixed << setprecision(6) << "Min dist = " << bestDist << "\n"
       << "Between points " << bestPair.first << " and " << bestPair.second
       << "\n";
  return 0;
}
