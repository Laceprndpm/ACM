#include <bits/stdc++.h>

#include <atcoder/all>
#include <atcoder/lazysegtree>
using namespace std;

int op(int a, int b)
{
    return max(a, b);
}

int e()
{
    return -1e9;
}

int mapping(int f, int x)
{
    return f + x;
}

int composition(int f, int g)
{
    return f + g;
}

int id()
{
    return 0;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& e : a)
        cin >> e;
    vector<int> dp(n, 0);
    vector<int> suml(n), sumr(n);
    int         now = 0;
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (++vis[a[i]] == 1) {
            now++;
        }
        suml[i] = now;
    }
    vis = vector<int>(n + 1, 0);
    now = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (++vis[a[i]] == 1) {
            now++;
        }
        sumr[i] = now;
    }
    atcoder::lazy_segtree<int, op, e, int, mapping, composition, id> seg(n);
    vector<int>                                                      last(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        seg.apply(last[a[i]] == -1 ? 0 : last[a[i]], i, 1);
        dp[i] = seg.prod(0, i);
        seg.set(i, suml[i]);
        last[a[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i < n - 1; ++i) {
        ans = max(ans, dp[i] + sumr[i + 1]);
    }
    cout << ans << endl;
}
