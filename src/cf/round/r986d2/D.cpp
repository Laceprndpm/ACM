#include <algorithm>
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

char who[] = {'q', 'k', 'j'};

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> arr(3, vector<int>(n + 1));
    vector<vector<int>> arr_p(3, vector<int>(n + 1));
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[j][i];
            arr_p[j][arr[j][i]] = i;
        }
    }
    vector<int> can_arrive(n + 1, 0);
    can_arrive[1] = 1;
    for (int i = 1; i <= n; i++) {
        if (can_arrive[i]) {
            for (int j = 0; j < 3; j++) {
                int ptrL = arr[j][0];
                int ptrR = arr[j][i];
                for (int k = ptrL + 1; k <= ptrR; k++) {
                    if (arr_p[j][k] > i) can_arrive[arr_p[j][k]] = j * n + i;
                }
                if (ptrL < ptrR) arr[j][0] = ptrR;
            }
        }
    }
    if (can_arrive[n]) {
        cout << "Yes\n";
        int         cur = n;
        vector<int> c;
        vector<int> num;
        num.push_back(n);
        while (cur != 1) {
            int last = can_arrive[cur];
            c.push_back(last / n);
            last %= n;
            cur = last;
            num.push_back(cur % n);
        }
        reverse(all(c));
        reverse(all(num));
        cout << sz(c) << '\n';
        for (int i = 0; i < sz(c); i++) {
            cout << who[c[i]] << ' ' << num[i + 1] << '\n';
        }
    } else {
        cout << "No\n";
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