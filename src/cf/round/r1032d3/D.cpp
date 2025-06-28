#include <cassert>
#include <format>
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

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int>    arr(n + 1), brr(n + 1);
    vector<string> cmd;
    auto           shift = [&](int who, int s, int e) {
        assert(s >= e);
        if (who == 0) {
            for (int i = s; i > e; i--) {
                cmd.push_back(format("1 {}", i - 1));
                swap(arr[i], arr[i - 1]);
            }
        } else {
            for (int i = s; i > e; i--) {
                cmd.push_back(format("2 {}", i - 1));
                swap(brr[i], brr[i - 1]);
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> brr[i];
    }
    int cntG = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] > n) {
            cntG++;
            shift(0, i, cntG);
        }
    }
    int cntL = 0;
    for (int i = 1; i <= n; i++) {
        if (brr[i] <= n) {
            cntL++;
            shift(1, i, cntL);
        }
    }
    assert(cntG == cntL);
    for (int i = 1; i <= cntG; i++) {
        cmd.push_back(format("3 {}", i));
        swap(arr[i], brr[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[j] == i) {
                shift(0, j, i);
            }
        }
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        for (int j = 1; j <= n; j++) {
            if (brr[j] == i) {
                shift(1, j, i - n);
            }
        }
    }
    cout << sz(cmd) << '\n';
    for (int i = 0; i < sz(cmd); i++) {
        cout << cmd[i] << '\n';
    }
    // cout << "arr:";
    // for (int i = 1; i <= n; i++) {
    //     cout << arr[i] << ' ';
    // }
    // cout << '\n';
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