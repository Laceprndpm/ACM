#include <bits/stdc++.h>
using namespace std;
using LL = long long;

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

string generateDict(int seed)
{
    string ans = "";
    while (seed > 0) {
        int remainder = (seed - 1) % 26;
        ans           = char('a' + remainder) + ans;
        seed          = (seed - 1) / 26;
    }
    return ans;
}

void solve()
{
    int    m;
    string inputString;
    cin >> m;
    cin >> inputString;
    vector<bool> cha(26, false);
    for (int i = 0; i < m; i++) {
        cha[(inputString[i] - 'a')] = true;
    }
    for (int i = 0; i < 26; i++) {
        if (!cha[i]) {
            cout << char(i + 'a') << '\n';
            return;
        }
    }
    int seed = 26;
    while (true) {
        seed++;
        string cnt = generateDict(seed);
        if (kmp(inputString, cnt) == -1) {
            cout << cnt << '\n';
            return;
        }
    }
}

signed main()
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