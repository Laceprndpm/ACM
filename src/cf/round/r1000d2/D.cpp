#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

vector<i64> initPrefix(list<int> x)
{
    vector<i64> value;
    int         n = x.size() / 2;
    for (int i = 1; i <= n; i++) {
        i64 l = x.front(), r = x.back();
        value.emplace_back(r - l);
        x.pop_front(), x.pop_back();
    }
    vector<i64> prefix(value.size() + 1);
    for (int i = 1; i <= value.size(); i++) {
        prefix[i] = prefix[i - 1] + value[i - 1];
    }
    return prefix;
}

template <typename F>
int binarySearchPeak(F f, int l, int r)
{
    while (l < r) {
        int m = l + (r - l) / 2;
        if (f(m) < f(m + 1)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    list<int> a, b;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a.push_back(tmp);
    }
    a.sort();
    for (int i = 0; i < m; i++) {
        int tmp;
        cin >> tmp;
        b.push_back(tmp);
    }
    b.sort();
    vector<i64> prefixA   = initPrefix(a);
    vector<i64> prefixB   = initPrefix(b);
    int         k         = 1;
    vector<int> kboundArr = {((n + m) / 3), n, m};
    int         kbound    = *min_element(kboundArr.begin(), kboundArr.end());
    cout << kbound << '\n';
    while (k <= kbound) {
        auto f = [&](int x) -> i64 {
            return prefixA[x] + prefixB[k - x];
        };
        int l = max(0, 2 * k - m);
        int r = min(k, n - k);
        cout << f(binarySearchPeak(f, l, r)) << ' ';
        k++;
    }
    cout << '\n';
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