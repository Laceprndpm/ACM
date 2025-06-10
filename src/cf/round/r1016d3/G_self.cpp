#include <bits/stdc++.h>

#include <algorithm>

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

constexpr int N   = 200000 * 31;
constexpr int INF = 1e9;
int           tot;
int           n, k;

int trie[N][2];
int recent[N];

int newNode()
{
    int x      = ++tot;
    trie[x][0] = trie[x][1] = 0;
    recent[x]               = 0;
    return x;
}

void init()
{
    tot = 0;
    newNode();
}

void add(int x, int t)
{
    int o = 1;
    for (int i = 30; i >= 0; i--) {
        int &p = trie[o][x >> i & 1];
        if (!p) {
            p = newNode();
        }
        o         = p;
        recent[o] = t;
    }
}

int query(int x)
{
    int o = 1;
    int ans;
    int atleast = -INF;
    for (int i = 30; i >= 0; i--) {
        int d = x >> i & 1;
        if ((k >> i & 1) == 0) {
            if (trie[o][d ^ 1]) {
                atleast = std::max(recent[trie[o][d ^ 1]], atleast);
                if (trie[o][d])
                    o = trie[o][d];
                else {
                    o = -1;
                    break;
                }
            } else {
                o = trie[o][d];
            }
        } else {
            if (trie[o][d ^ 1]) {
                o = trie[o][d ^ 1];
            } else {
                o = -1;
                break;
            }
        }
    }
    if (o != -1) {
        ans = recent[o];
    } else {
        ans = -INF;
    }
    return std::max(ans, atleast);
}

void solve()
{
    std::cin >> n >> k;

    init();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int ans = n + 1;

    for (int i = 0; i < n; i++) {
        ans = std::min(ans, i - query(a[i]) + 1);
        add(a[i], i);
    }

    if (ans > n) {
        ans = -1;
    }
    std::cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
