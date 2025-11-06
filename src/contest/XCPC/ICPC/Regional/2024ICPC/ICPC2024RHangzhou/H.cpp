#include <bits/stdc++.h>

#include <utility>
#include <vector>

using namespace std;
// vector
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mt      make_tuple
#define fi      first
#define se      second
using i64 = long long;
using u64 = unsigned long long;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> hld(k);
    for (int i = 0; i < k; i++) {
        cin >> hld[i].fi >> hld[i].se;
    }
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }
    vector<int> fa(n + 1);
    sort(all(hld), [](const pair<int, int>& a, const pair<int, int>& b) { return a.se - a.fi > b.se - b.fi; });
    int last = 0;

    for (int i = hld[0].fi; i <= hld[0].se; i++) {
        fa[i] = last;
        last  = i;
    }
    if (hld[0].se - hld[0].fi == hld[1].se - hld[1].fi) {
        if (hld.bk.se - hld.bk.fi <= hld[0].se - hld[0].fi - 2) {
            last = hld[0].fi + 1;
        } else {
            cout << "IMPOSSIBLE\n";
            return;
        }
        for (int i = hld.bk.fi; i <= hld.bk.se; i++) {
            fa[i] = last;
            last  = i;
        }
        for (int j = 1; j < k - 1; j++) {
            last = hld[0].fi;
            for (int i = hld[j].fi; i <= hld[j].se; i++) {
                fa[i] = last;
                last  = i;
            }
        }
    } else {
        for (int j = 1; j < k; j++) {
            last = hld[0].fi;
            for (int i = hld[j].fi; i <= hld[j].se; i++) {
                fa[i] = last;
                last  = i;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << fa[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}