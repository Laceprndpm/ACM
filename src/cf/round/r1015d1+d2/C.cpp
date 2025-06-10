#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class Permutation {
    int         n;
    vector<int> v2p;
    vector<int> p2v;

public:
    Permutation(const vector<int>& vec) : n(vec.size() - 1), v2p(vec), p2v(vec.size())  // 0-index
    {
        for (int i = 0; i <= n; i++) {
            p2v[v2p[i]] = i;
        }
    }

    Permutation(vector<int>&& vec) : n(vec.size() - 1), v2p(std::move(vec)), p2v(v2p.size())
    {
        for (int i = 0; i <= n; i++) {
            p2v[v2p[i]] = i;
        }
    }

    void swap(int i, int j)
    {
        assert(i <= n && i >= 0 && j <= n && j >= 0 && i != j);
        std::swap(v2p[i], v2p[j]);
        p2v[v2p[i]] = i;
        p2v[v2p[j]] = j;
    }

    int operator[](int i) const
    {
        assert(i >= 0 && i <= n);
        return v2p[i];
    }

    int operator()(int i) const
    {
        assert(i >= 0 && i <= n);
        return p2v[i];
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a2p(n + 1);
    vector<int> b2p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a2p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b2p[i];
    }
    Permutation              a(std::move(a2p));
    Permutation              b(std::move(b2p));
    function<void(int, int)> sw = [&](int i, int j) -> void {
        a.swap(i, j);
        b.swap(i, j);
    };
    vector<pair<int, int>> ans;
    if (n % 2) {
        int i;
        for (i = 1; i <= n; i++) {  // 假设a的位置是对的...
            if (a[i] == b[i]) {
                break;
            }
        }
        if (i == n + 1) {
            cout << -1 << '\n';
            return;
        }
        if (i != n / 2 + 1) {
            ans.emplace_back(i, n / 2 + 1);
            sw(i, n / 2 + 1);
        }
    }
    for (int j = 1; j <= n; j++) {
        if (b[n + 1 - a(j)] != j) {
            ans.emplace_back(b(j), n + 1 - a(j));
            sw(b(j), n + 1 - a(j));
        }
    }
    for (auto& i : ans) {
        if (i.first > i.second) {
            swap(i.first, i.second);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[n + 1 - i]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i.first << ' ' << i.second << '\n';
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    2 freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}