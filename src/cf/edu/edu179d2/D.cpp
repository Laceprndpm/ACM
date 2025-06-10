#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
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
#define int     long long
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> mrr(m);
    for (int& i : mrr) {
        cin >> i;
    }
    sor(mrr);
    int p1 = 0, p2 = m - 1;
    // int pp1 = 0, pp2 = m - 1;

    vector<pair<int, int>> cls(n);
    // vector<pair<int, int>> cls2(n);

    i64 ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++) {
        cls[i] = {mrr[p1], mrr[p2]};
        // cls2[i] = {mrr[pp1], mrr[pp2]};
        ans1 += abs(mrr[p1] / 100 - mrr[p2] / 100);
        // ans2 += abs(mrr[pp1] / 100 - mrr[pp2] / 100);
        if (i % 2) {
            p1++;
            p2--;
            // pp2--;
        } else {
            // pp1++;
        }
    }
    // if (ans2 > ans1) swap(cls, cls2);
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            swap(cls[i].first, cls[i].second);
        }
        for (int j = 0; j < 3; j++) {
            cout << cls[i].first << ' ' << cls[i].second << ' ';
        }
        cout << '\n';
    }
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */