#include <bits/stdc++.h>
using namespace std;
const int ALPHA = 256;

// build bad-char table
vector<int> buildBadChar(const string &pat) {
  vector<int> bad(ALPHA, -1);
  for (int i = 0; i < (int)pat.size(); i++)
    bad[(unsigned char)pat[i]] = i;
  return bad;
}

// build good-suffix table
vector<int> buildGoodSuffix(const string &pat) {
  int m = pat.size();
  vector<int> suff(m), good(m + 1);
  suff[m - 1] = m;
  int g = m - 1, f = 0;
  for (int i = m - 2; i >= 0; --i) {
    if (i > g && suff[i + m - 1 - f] < i - g)
      suff[i] = suff[i + m - 1 - f];
    else {
      if (i < g)
	g = i;
      f = i;
      while (g >= 0 && pat[g] == pat[g + m - 1 - f])
	g--;
      suff[i] = f - g;
    }
  }
  fill(good.begin(), good.end(), m);
  int j = 0;
  for (int i = m - 1; i >= 0; --i)
    if (suff[i] == i + 1)
      for (; j < m - 1 - i; ++j)
	good[j] = m - 1 - i;
  for (int i = 0; i <= m - 2; ++i)
    good[m - 1 - suff[i]] = m - 1 - i;
  return good;
}

vector<int> boyerMoore(const string &txt, const string &pat) {
  int n = txt.size(), m = pat.size();
  auto bad = buildBadChar(pat);
  auto good = buildGoodSuffix(pat);
  vector<int> occ;
  int s = 0;
  while (s <= n - m) {
    int j = m - 1;
    while (j >= 0 && pat[j] == txt[s + j])
      j--;
    if (j < 0) {
      occ.push_back(s);
      s += good[0];
    } else {
      s += max(good[j + 1], j - bad[(unsigned char)txt[s + j]]);
    }
  }
  return occ;
}

int main() {
  string txt, pat;
  getline(cin, txt);
  getline(cin, pat);
  auto res = boyerMoore(txt, pat);
  for (int idx : res)
    cout << "Pattern at index " << idx << "\n";
  return 0;
}
