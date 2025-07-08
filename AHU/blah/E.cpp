#include <algorithm>
#include <cstring>
#include <iostream>
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
int           t;
constexpr i64 N = 1 << 20;
int           arr[N];

void solve(int test)
{
    i64 n;
    cin >> n;
    memset(arr, 0, sizeof(arr));
    vector<int> ok;
    int         cntsp = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == N) {
            cntsp++;
            continue;
        }
        if (arr[x]) {
            ok.push_back(x);
        }
        arr[x] = x;
    }
    if (cntsp >= 2) {
        cout << "Case #" << test + 1;
        cout << ": ";
        cout << N << '\n';
        return;
    }
    // 2097152 * 21 * 10 = 4e8
    i64 candi = *max_element(all(ok));
    for (int i = N - 1; i >= candi; i--) {
        for (int j = 0; j < 20; j++) {
            if (i >> j & 1) continue;
            if (arr[i | (1 << j)] == 0) continue;

            if (arr[i] == 0) {
                arr[i] = arr[i | (1 << j)];
            }

            if (arr[i] != arr[i | (1 << j)]) {
                cout << "Case #" << test + 1;
                cout << ": ";
                cout << i << '\n';
                return;
            }
        }
    }
    cout << "Case #" << test + 1;
    cout << ": ";
    cout << candi << '\n';
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
    // 1 3  5   7
    // 1 11 101 111
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve(i);
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