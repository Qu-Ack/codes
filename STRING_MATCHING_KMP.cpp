#include <bits/stdc++.h>
using namespace std;

vector<int> buildLPS(const string &pat) {
  int m = pat.size();
  vector<int> lps(m);
  int len = 0, i = 1;
  lps[0] = 0;
  while (i < m) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i++] = len;
    } else if (len) {
      len = lps[len - 1];
    } else {
      lps[i++] = 0;
    }
  }
  return lps;
}

vector<int> kmpSearch(const string &txt, const string &pat) {
  int n = txt.size(), m = pat.size();
  auto lps = buildLPS(pat);
  vector<int> occ;
  int i = 0, j = 0;
  while (i < n) {
    if (txt[i] == pat[j]) {
      i++;
      j++;
      if (j == m) {
	occ.push_back(i - j);
	j = lps[j - 1];
      }
    } else if (j) {
      j = lps[j - 1];
    } else {
      i++;
    }
  }
  return occ;
}

int main() {
  string txt, pat;
  getline(cin, txt);
  getline(cin, pat);
  auto res = kmpSearch(txt, pat);
  for (int idx : res)
    cout << "Pattern at index " << idx << "\n";
  return 0;
}
