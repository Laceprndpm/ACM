#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define ls               (p << 1)
#define rs               (p << 1 | 1)
#define mid              ((l + r) >> 1)
#define all(_array)      (_array).begin(), (_array).end()
#define msp(_array)      memset(_array, 0x3f, sizeof _array)
#define ms0(_array)      memset(_array, 0, sizeof _array)
#define msn(_array)      memset(_array, -1, sizeof _array)
#define mc(_tar, _array) memcpy(_tar, _array, sizeof _tar)
#define Yes              cout << "Yes" << endl, void()
#define No               cout << "No" << endl, void()
#define YES              cout << "YES" << endl, void()
#define NO               cout << "NO" << endl, void()
#define yes              cout << "yes" << endl, void()
#define no               cout << "no" << endl, void()
#define TAK              cout << "TAK" << endl, void()
#define NIE              cout << "NIE" << endl, void()
#define OK               cerr << "OK" << endl, void()
#define pii              pair<int, int>
#define endl             '\n'

bool                                  bg_memory;
mt19937_64                            rnd(time(0));
chrono::_V2::system_clock::time_point bg_clock, en_clock;
int                                   Case = 1;
const int                             mod  = 1e9 + 7;
const int                             inf  = 1e7;
const int                             bs   = 233;
const double                          eps  = 1e-6;
const int                             N = 400 + 7, M = 200 + 7;

template <class _t1, class _t2>
inline void cmax(_t1 &a, _t2 b)
{
    a = a < b ? b : a;
}

template <class _t1, class _t2>
inline void cmin(_t1 &a, _t2 b)
{
    a = a > b ? b : a;
}

inline int qp(int a, int b, int p = mod)
{
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return res;
}

inline int sqrt(int x, int r)
{
    int l = 0, ans = 0;
    while (l <= r) {
        if (1ll * mid * mid <= x)
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}

int n, m, k = 200;
int diff_arr[N], mx;
int ans;
int dp[N][M][2];

void Main()
{

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> diff_arr[i], cmax(mx, diff_arr[i]);
    if (n == 1) return cout << 0 << endl, void();
    ans = 0;
    if (m == 1) {
        int ni = -1;
        for (int i = 1; i <= n; i++) cmax(ni, mx - diff_arr[i]);
        for (int _ = 1; _ <= ni; _++) {
            for (int i = 2; i <= n + 1; i++) {
                if (i == n + 1 || diff_arr[i] == mx) ans += (diff_arr[i - 1] != mx);
            }
            for (int i = 1; i <= n; i++) diff_arr[i] = min(mx, diff_arr[i] + 1);
        }
        cout << ans << endl;
    } else {
        ans = inf;
        for (int i = n; i >= 2; i--) diff_arr[i] = diff_arr[i] - diff_arr[i - 1];
        for (int delta = 0; delta <= k; delta++) {
            msp(dp);
            for (int j = 0; j <= k; j++)
                dp[1][j][0] = dp[1][j][1] =
                    j;  // [i][j][k] i是第几个，j是有多少个没有匹配的-1，0/1表示上一个是-delta或者+delta
            for (int i = 2; i <= n; i++) {
                for (int j = 0; j <= k; j++) {                      // 枚举上一个j
                                                                    // 都是将diff变成0
                    if (diff_arr[i] > 0 && diff_arr[i] - j <= 0) {  // 如果当前>0，且上一个的所有-1数量可以把当前降低到0
                        cmin(dp[i][j - diff_arr[i]][0], dp[i - 1][j][0]);
                        cmin(dp[i][j - diff_arr[i]][1], dp[i - 1][j][1]);
                    }
                    if (diff_arr[i] <= 0) {  // 如果当前<=0，则扩大待匹配的-1数
                        cmin(dp[i][j - diff_arr[i]][0], dp[i - 1][j][0] - diff_arr[i]);
                        cmin(dp[i][j - diff_arr[i]][1], dp[i - 1][j][1] - diff_arr[i]);
                    }
                    if (diff_arr[i] > delta && diff_arr[i] - j <= delta) {  // 如果当前的值>delta，变成delta
                        cmin(dp[i][j - (diff_arr[i] - delta)][0], dp[i - 1][j][1]);
                    }
                    if (diff_arr[i] <= delta) {  // 当前的值<delta，变成delta
                        cmin(dp[i][j - (diff_arr[i] - delta)][0], dp[i - 1][j][1] - (diff_arr[i] - delta));
                    }
                    if (diff_arr[i] > -delta && diff_arr[i] - j <= -delta) {  // 当前的值>-delta
                        cmin(dp[i][j - (diff_arr[i] + delta)][1], dp[i - 1][j][0]);
                    }
                    if (diff_arr[i] <= -delta) {  // 当前的值<=-delta
                        cmin(dp[i][j - (diff_arr[i] + delta)][1], dp[i - 1][j][0] - (diff_arr[i] + delta));
                    }
                }
            }
            for (int j = 0; j <= k; j++) cmin(ans, dp[n][j][0]), cmin(ans, dp[n][j][1]);
            // cout<<d<<" "<<ans<<endl;
        }
        cout << ans << endl;
    }

    return;
}

string RdFile = "woodguy";
bool   en_memory;

signed main()
{
    bg_clock = chrono::high_resolution_clock::now();
    // #ifdef ONLINE_JUDGE
    // freopen((RdFile+".in").c_str(),"r",stdin);
    // freopen((RdFile+".out").c_str(),"w",stdout);
    // #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> Case;
    while (Case--) Main();
    en_clock              = chrono::high_resolution_clock::now();
    auto   duration_clock = chrono::duration_cast<chrono::microseconds>(en_clock - bg_clock);
    double duration_count = duration_clock.count() * 0.001;
    double memory_used    = (&en_memory - &bg_memory) / 1024.0 / 1024;
    // cerr<<"Time:"<<duration_count<<"ms"<<endl;
    // cerr<<"Memory: "<<memory_used<<"MB"<<endl;
    return 0;
}