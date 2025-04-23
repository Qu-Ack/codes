#include <bits/stdc++.h>
using namespace std;

// d = alphabet size, q = a prime modulus
vector<int> rabinKarp(const string &txt, const string &pat, int q) {

  int n = txt.size(), m = pat.size(), d = 256;
  int h = 1, p = 0, t = 0;
  vector<int> occ;

  // h = pow(d, m-1) % q
  for (int i = 0; i < m - 1; i++)
    h = (h * d) % q;

  // initial hash values
  for (int i = 0; i < m; i++) {
    p = (d * p + pat[i]) % q;
    t = (d * t + txt[i]) % q;
  }

  // slide pattern
  for (int i = 0; i <= n - m; i++) {
    if (p == t) {
      // verify on hash match
      bool match = true;
      for (int j = 0; j < m; j++)
	if (txt[i + j] != pat[j]) {
	  match = false;
	  break;
	}
      if (match)
	occ.push_back(i);
    }
    // compute next window hash
    if (i < n - m) {
      t = (d * (t - txt[i] * h) + txt[i + m]) % q;
      if (t < 0)
	t += q;
    }
  }
  return occ;
}

int main() {
  string txt, pat;
  int q = 101;
  getline(cin, txt);
  getline(cin, pat);
  auto res = rabinKarp(txt, pat, q);
  for (int idx : res)
    cout << "Pattern at index " << idx << "\n";
  return 0;
}
