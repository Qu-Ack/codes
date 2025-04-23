#include <bits/stdc++.h>
using namespace std;

struct Item {
  int weight;
  int value;
};

bool cmp(const Item &a, const Item &b) {
  double r1 = (double)a.value / a.weight;
  double r2 = (double)b.value / b.weight;
  return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &items) {
  sort(items.begin(), items.end(), cmp);

  double totalValue = 0.0;
  int remaining = W;
  for (auto &it : items) {
    if (it.weight <= remaining) {
      remaining -= it.weight;
      totalValue += it.value;
    } else {
      totalValue += (double)it.value * remaining / it.weight;
      break;
    }
  }
  return totalValue;
}

int main() {
  int n, W;
  cin >> n >> W;
  vector<Item> items(n);
  for (int i = 0; i < n; i++)
    cin >> items[i].weight >> items[i].value;
  cout << fixed << setprecision(2) << fractionalKnapsack(W, items) << "\n";
  return 0;
}
