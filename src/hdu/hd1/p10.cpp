#include <bits/stdc++.h>

#include <cassert>
#include <iostream>
#include <vector>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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
#define len(x)  int(x.size())
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
#define mp      make_pair
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }
    i64           ans = 0;
    vector<int>   prefix(n + 1), suffix(n + 1);
    vector<int>   buffer(5000);
    constexpr int offsit = 2025;
    vector<int>   dirty  = buffer;
    for (i64 i = 1; i <= n; i++) {
        i64 post = pos[i];
        int les = 0, gre = 0;
        dirty[offsit]  = i;
        buffer[offsit] = post;
        for (i64 j = post - 1; j >= 1; j--) {
            if (arr[j] < i)
                les++;
            else
                gre++;
            if (dirty[gre - les + offsit] != i) {
                dirty[gre - les + offsit]  = i;
                buffer[gre - les + offsit] = 0;
            }
            buffer[gre - les + offsit] += j;
        }
        les = 0, gre = 0;
        ans += buffer[offsit] * post * i;
        for (i64 j = post + 1; j <= n; j++) {
            if (arr[j] < i)
                les++;
            else
                gre++;
            if (dirty[les - gre + offsit] == i) {
                ans += j * i * buffer[les - gre + offsit];
            }
        }
    }
    // for (i64 i = 1; i <= n; i++) {
    //     priority_queue<int, vector<int>, less<>>    pq_L;
    //     priority_queue<int, vector<int>, greater<>> pq_R;
    //     pq_L.push(arr[i]);
    //     for (i64 j = i; j <= n; j += 2) {
    //         ans += i * j * pq_L.top();
    //         // pq_L.push(arr[j + 1]);
    //         // pq_L.push(arr[j + 2]);
    //         for (int k = 1; k <= 2; k++) {
    //             if (pq_L.empty() || arr[j + k] <= pq_L.top())
    //                 pq_L.push(arr[j + k]);
    //             else
    //                 pq_R.push(arr[j + k]);

    //             if (pq_L.size() > pq_R.size() + 1) {
    //                 pq_R.emplace(pq_L.top());
    //                 pq_L.pop();
    //             } else if (pq_L.size() < pq_R.size()) {
    //                 pq_L.emplace(pq_R.top());
    //                 pq_R.pop();
    //             }
    //         }
    //     }
    // }
    cout << ans << '\n';
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