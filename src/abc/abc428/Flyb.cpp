#include <algorithm>
#include <iostream>
#include <map>

#define endl '\n'
#define ios  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
typedef long long LL;

const int N = 2e5 + 10;

int                     n;
LL                      w[N];
map<int, pair<int, LL>> mp;

LL gets(int i)
{
    auto it = mp.lower_bound(i);
    if (it == mp.end()) {
        return 0;
    }
    int op = it->second.first;
    return op == 1 ? it->second.second : it->second.second - w[i - 1];
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
    }
    int q;
    cin >> q;
    mp.clear();
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int v;
            cin >> v;
            LL   l  = gets(v);
            auto it = mp.begin();
            while (it != mp.end() && it->first <= v) {
                it = mp.erase(it);
            }
            mp[v] = {1, l};
        } else if (op == 2) {
            int v;
            cin >> v;
            LL   l  = gets(v);
            LL   r  = l + w[v - 1];
            auto it = mp.begin();
            while (it != mp.end() && it->first <= v) {
                it = mp.erase(it);
            }
            mp[v] = {2, r};
        } else {
            LL x;
            cin >> x;
            LL  ans = 0;
            int lst = 0;
            for (auto const &[v, op] : mp) {
                int ll = lst + 1;
                int rr = v;
                if (ll > rr) {
                    lst = v;
                    continue;
                }
                if (op.first == 1) {
                    LL val = op.second;
                    if (val <= x) {
                        auto it = upper_bound(w + ll - 1, w + rr, x - val);
                        ans += (w + rr) - it;
                    }
                } else {
                    LL val = op.second;
                    if (val > x) {
                        auto it = lower_bound(w + ll - 1, w + rr, val - x);
                        ans += (w + rr) - it;
                    }
                }
                lst = v;
            }
            if (lst < n) {
                if (0 <= x) {
                    auto it = upper_bound(w + lst, w + n, x);
                    ans += (w + n) - it;
                }
            }
            cout << ans << endl;
        }
    }
}

signed main()
{
    ios;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}