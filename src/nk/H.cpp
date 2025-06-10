#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

string no(string s)
{
    string ans;
    for (char c : s) {
        ans += (c == '1') ? '0' : '1';
    }
    return ans;
}

bool check(string s, int n)
{
    for (int i = 0; i < (i64)s.length(); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            int ii = i ^ (1 << j);
            if (s[ii] == s[i]) cnt++;
        }
        if (cnt > ceil(sqrt(n))) return false;
    }
    return true;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    constexpr int len = 1 << 22;
    string        s   = "1";
    while ((i64)s.length() < (1 << n)) {
        s += no(s);
    }
    bool flag = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (s[i] == '0') continue;
        s[i] = '0';
        if (check(s, n)) {
            flag = 1;
            cout << "BINGGO\n";
            break;
        } else
            s[i] = '1';
    }
    if (!check(s, n) || !flag) assert(0);
    cout << s << '\n';
    return 0;
}