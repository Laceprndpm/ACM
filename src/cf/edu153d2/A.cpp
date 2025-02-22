// (((()))) || ()()()()
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

int kmp(const string& text, const string& pattern)
{
    int n = text.size(), m = pattern.size();
    if (m == 0) {
        return 0;
    }
    vector<int> next(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1;
        }
    }
    return -1;
}

void solve()
{
    string input;
    cin >> input;
    if (input == string("()")) {
        cout << "NO\n";
        return;
    } else {
        cout << "YES\n";
        int    half_n = input.length();
        string ans1   = "";
        string ans2   = "";
        for (int i = 0; i < half_n; i++) {
            ans1 += "(";
        }
        for (int i = 0; i < half_n; i++) {
            ans1 += ")";
        }
        for (int i = 0; i < half_n; i++) {
            ans2 += "()";
        }
        if (kmp(ans1, input) != -1) {
            cout << ans2 << '\n';
            return;
        } else {
            cout << ans1 << '\n';
            return;
        }
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}