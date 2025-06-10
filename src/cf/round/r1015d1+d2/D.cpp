#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i + 1 < vec.size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    // 假设f(b)=x
    // 那么，0-x，每个元素数量为m+1，且每个间有k-1以上个数字
    // function<bool(int)> check = [&](int x) -> bool {
    //     bool res = ((x * (m + 1) <= n) && (k * (m + 1) <= n));
    //     return res;
    // };
    int         x = n / (m + 1);
    vector<int> ans(n);
    if (x >= k) {
        for (int i = 0; i < n; i++) {
            ans[i] = i % x;
        }
    } else {
        for (int i = 0; i < n; i++) {
            ans[i] = i % k;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main(int argc, char** argv)
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