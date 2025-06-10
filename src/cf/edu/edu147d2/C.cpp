#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

// 假如确定某字符c来保存，不删c一定最优？最优
// 假如cxxxxxc，中间的x为将被移除的，那么每次可以移除一半，或者说保留len/2下取整

int fxxk(int x)
{
    int cnt = 0;
    while (x) {
        x /= 2;
        cnt++;
    }
    return cnt;
}

void solve()
{
    string s;
    cin >> s;
    int         slength = s.length();
    vector<int> lastidx(26, -1);
    vector<int> maxlen(26, 0);
    vector<int> appear(26);
    for (int i = 0; i < slength; i++) {
        char cur           = s[i];
        maxlen[cur - 'a']  = max(i - lastidx[cur - 'a'] - 1, maxlen[cur - 'a']);
        lastidx[cur - 'a'] = i;
    }

    for (char cur = 'a'; cur <= 'z'; cur++) {
        maxlen[cur - 'a'] = max(slength - lastidx[cur - 'a'] - 1, maxlen[cur - 'a']);
    }

    int minMaxlen = INF;
    for (char i = 'a'; i <= 'z'; i++) {
        minMaxlen = min(minMaxlen, maxlen[i - 'a']);
    }
    cout << fxxk(minMaxlen) << '\n';
    return;
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}