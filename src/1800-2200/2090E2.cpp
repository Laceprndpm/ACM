#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
#define int long long

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
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }

    if (k == accumulate(all(arr), 0ll)) {
        cout << 0 << '\n';
        return;
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = arr[i] - brr[i];
    }
    vector<int> cPre(1, 0);
    cPre.reserve((int)(c).size() + 1);
    for (int it : c) {
        cPre.eb(cPre.back() + it);
    }
    int tail = min_element(bg(cPre) + 1, cPre.end()) - cPre.begin() - 1;
    int head = (tail + 1) % n;
    {
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = arr[(head + i) % n];
        }
        arr = temp;
        for (int i = 0; i < n; i++) {
            temp[i] = brr[(head + i) % n];
        }
        brr = temp;
        for (int i = 0; i < n; i++) {
            temp[i] = c[(head + i) % n];
        }
        c = std::move(temp);
        cPre.resize(1);
        for (int it : c) {
            cPre.eb(cPre.back() + it);
        }
    }
    auto check = [&](int x) -> bool {
        int        need = 0;
        deque<int> q;
        for (int i = n; i >= 0; i--) {
            if (!q.empty() && q.front() - i > x) {
                q.pop_front();
            }
            if (!q.empty()) need += max(cPre[q.front()] - cPre[i], 0ll);
            while (!q.empty() && cPre[q.back()] >= cPre[i]) {
                q.pop_back();
            }
            q.eb(i);
        }
        return need <= k;
        // int mnPre = INF;
        // cPre.resize(1);
        // for (int i = 0; i < n; i++) {
        //     cPre.eb(cPre.back() + c[i]);
        //     if (i - x + 1 >= 0) {
        //         mnPre = min(mnPre, cPre[i - x + 1]);
        //     }
        //     if (cPre[i + 1] - mnPre > 0) {
        //         need += cPre[i + 1] - mnPre;
        //         cPre[i + 1] = mnPre;
        //     }
        // }
        // return need <= k;
    };
    int l = 1, r = n;
    int ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
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