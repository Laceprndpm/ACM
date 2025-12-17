#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

struct ODT {
    i64 val = 0;

    struct node {
        int        l, r;
        mutable ll v;

        node(int l, int r = -1, ll v = 0) : l(l), r(r), v(v) {}

        bool operator<(const node& o) const { return l < o.l; }
    };

    set<node> s;

    ODT() { s.clear(); }

    auto split(int pos)
    {
        auto it = s.lower_bound(node(pos));
        if (it != s.end() && it->l == pos) return it;
        it--;
        int l = it->l, r = it->r;
        ll  v = it->v;
        s.erase(it);
        s.insert(node(l, pos - 1, v));
        return s.insert(node(pos, r, v)).first;
    }

    void assign(int l, int r, ll x)
    {
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; it++) {
            val -= (it->r - it->l + 1) * it->v;
        }
        s.erase(itl, itr);
        s.insert(node(l, r, x));
        val += (r - l + 1) * x;
    }
};

void solve()
{
    ODT odt;
    int n, q;
    cin >> n >> q;
    odt.s.insert({1, n, 0});
    while (q--) {
        int l, r;
        cin >> l >> r;
        odt.assign(l, r, 1);
        cout << n - odt.val << '\n';
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
    int t = 1;
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