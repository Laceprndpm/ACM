
// from Starsilk
#include <bits/stdc++.h>
using namespace std;
string s, cs;
int    cnt[26], cur[26];

int check()
{
    int n = s.length(), i;
    for (i = 0; i < 26; i++) {
        cnt[i] = 0;
        cur[i] = 0;
    }
    for (i = 0; i < n; i++)
        cnt[s[i] - 'a']++;
    for (i = 0; i < n / 2; i++) {
        cur[s[i] - 'a']++;
        if (cur[s[i] - 'a'] * 2 > cnt[s[i] - 'a'])
            return n - i;
    }
    if (n % 2 == 1) {
        if (cnt[s[n / 2] - 'a'] % 2 != 1)
            return n - n / 2;
    }
    for (i = (n + 1) / 2; i < n; i++) {
        if (s[i] != s[n - i - 1])
            return n - i;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, i, p, ans;
    for (cin >> T; T > 0; T--) {
        cin >> s;
        n = s.length();
        p = -1;
        for (i = 0; i < n; i++) {
            if (s[i] != s[n - i - 1]) {
                p = i;
                break;
            }
        }
        if (p == -1) {
            cout << "0\n";
            continue;
        }
        for (i = p; i <= n - p - 1; i++)
            cs.push_back(s[i]);
        s = cs;
        cs.clear();
        n   = s.length();
        ans = check();
        for (i = n - 1; i > -1; i--)
            cs.push_back(s[i]);
        s = cs;
        cs.clear();
        ans = min(ans, check());
        cout << ans << '\n';
    }
    return 0;
}