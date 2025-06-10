#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
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

constexpr i64 INF = 1e9 + 50;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> bi(n);
    for (int i = 0; i < n; i++) {
        cin >> bi[i];
    }
    vector<int> xi(q), yi(q), zi(q);
    for (int i = 0; i < q; i++) {
        cin >> xi[i] >> yi[i] >> zi[i];
        xi[i]--, yi[i]--, zi[i]--;
    }
    vector<vector<int>> g(n);
    vector<int>         cur_head(n);
    vector<int>         deg(n);
    iota(all(cur_head), 0);
    int cnt = n;
    for (int i = 0; i < q; i++) {
        int x = xi[i], y = yi[i], z = zi[i];
        x = cur_head[x], y = cur_head[y];
        cur_head[z] = cnt++;

        int n_z = cur_head[z];
        g.push_back({});
        deg.push_back(0);
        deg[x]++, deg[y]++;
        g[n_z].push_back(x), g[n_z].push_back(y);  // x >= z
    }
    vector<int> val(cnt, 0);
    deque<int>  que;
    for (int i = 0; i < n; i++) {
        val[cur_head[i]] = bi[i];
    }
    for (int i = 0; i < cnt; i++) {
        if (deg[i] == 0) {
            que.push_back(i);
        }
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop_front();
        for (int adj : g[cur]) {
            val[adj] = max(val[adj], val[cur]);
            deg[adj]--;
            if (deg[adj] == 0) que.push_back(adj);
        }
    }
    vector<int> ai(n);
    for (int i = 0; i < n; i++) {
        ai[i] = val[i];
    }

    auto check = [&](void) -> bool {
        vector<int> tmp = ai;
        for (int i = 0; i < q; i++) {
            int x = xi[i], y = yi[i], z = zi[i];
            tmp[z] = min(tmp[x], tmp[y]);
        }
        return tmp == bi;
    };

    if (check()) {
        for (int i = 0; i < n; i++) {
            cout << ai[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << -1 << '\n';
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
// for (int i = 0; i < n; i++) {
//     cout << ai[i] << ' ';
// }
// cout << '\n';
// bool ok = 1;
// for (int i = q - 1; i >= 0; i--) {
//     int x = xi[i], y = yi[i], z = zi[i];
//     if (bi[z] > min(bi[x], bi[y])) {
//         ok = false;
//     }
// }
// 从后往前枚举
// 那么，当前一定是必然状态？
// 对，一定可以到达bi
//
// 除了free_arr
// 如果当前的xi == zi
// 则只查看yi，如果[yi] == [zi]
// 则zi进入自由状态
// 否则只要有一个[xi], [yi] == [zi]
// zi都可以进入自由状态
// 如果某个状态zi <= xi
// 但是xi可以自由
// 则可以勒令xi = zi
//
//
// vector<int> free_arr(n, 0);
// for (int i = q - 1; i >= 0; i--) {
//     int x = xi[i], y = yi[i], z = zi[i];
//     if (x != z) {
//         swap(x, y);
//     }
//     if (tmp[z] > tmp[x]) {
//         if (free_arr[x]) {

//             tmp[x] = tmp[z];
//         } else {
//             break;
//         }
//     }
//     if (tmp[z] > tmp[y]) {
//         if (free_arr[y]) {

//             tmp[y] = tmp[z];
//         }
//     }
//     if (x == z) {
//         if (tmp[z] == tmp[x]) {
//             free_arr[z] = 1;
//             tmp[z]      = -1;
//         }
//     } else {
//         if (tmp[z] == min(tmp[x], tmp[y])) {
//             free_arr[z] = 1;
//             tmp[z]      = -1;
//         }
//     }
// }
// for (int i = 0; i < n; i++) {
//     if (tmp[i] == -1) {
//         tmp[i] = bi[i];
//     }
// }
// ai = tmp;
// for (int i = 0; i < q; i++) {
//     int x = xi[i], y = yi[i], z = zi[i];
//     if (tmp[x] < bi[z]) {
//         tmp[x] = ai[x] = bi[z];
//     }
//     if (tmp[y] < bi[z]) {
//         tmp[y] = ai[y] = bi[z];
//     }
//     tmp[z] = min(tmp[y], tmp[x]);
// }