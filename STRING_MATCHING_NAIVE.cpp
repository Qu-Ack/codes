#include <bits/stdc++.h>
using namespace std;

vector<int> naiveSearch(const string &txt, const string &pat) {
  int n = txt.size(), m = pat.size();
  vector<int> occurrences;
  for (int i = 0; i <= n - m; i++) {
    int j = 0;
    while (j < m && txt[i + j] == pat[j]) {
      j++;
    }
    if (j == m) {
      occurrences.push_back(i);
    }
  }
  return occurrences;
}

int main() {
  string txt, pat;
  getline(cin, txt);
  getline(cin, pat);
  auto occ = naiveSearch(txt, pat);
  for (int idx : occ) {
    cout << "Pattern at index " << idx << "\n";
  }
  return 0;
}
