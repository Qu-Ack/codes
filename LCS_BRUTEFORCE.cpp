#include <iostream>
#include <string>
using namespace std;

/** Return true if `sub` is a subsequence of `str`. */
bool isSubsequence(const string &sub, const string &str) {
    int j = 0;
    for (int i = 0; i < (int)str.size() && j < (int)sub.size(); i++) {
        if (str[i] == sub[j]) {
            j++;
        }
    }
    return j == (int)sub.size();
}

/** Brute-force LCS: generate all subsequences of the shorter string. */
string bruteForceLCS(const string &s1, const string &s2) {
    // Always enumerate subsequences of the shorter string
    const string &small = (s1.size() <= s2.size() ? s1 : s2);
    const string &large = (s1.size() <= s2.size() ? s2 : s1);

    int n = small.size();
    string best = "";
    int total = 1 << n;  // 2^n subsequences :contentReference[oaicite:6]{index=6}

    for (int mask = 0; mask < total; mask++) {
        // Quick pruning: max possible length from this mask
        int bits = __builtin_popcount(mask);
        if (bits <= (int)best.size()) continue;

        // Build subsequence for this mask
        string sub;
        sub.reserve(bits);
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sub.push_back(small[i]);
            }
        }

        // Test and update best
        if (isSubsequence(sub, large) && sub.size() > best.size()) {
            best = move(sub);
        }
    }
    return best;
}

int main() {
    string s1 = "AGGTAB", s2 = "GXTXAYB";
    string lcs = bruteForceLCS(s1, s2);
    cout << "LCS = " << lcs << "\n";  // prints "GTAB"
    return 0;
}
