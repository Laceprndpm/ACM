#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class TreeArr {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    TreeArr(int _n)
    {
        bitArr.resize(_n + 1, 0);
    }

    void update(int place, int value)
    {
        for (int i = place; i < bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    int query(int place)
    {
        int res = 0;
        for (int i = place; i; i -= lowbit(i)) {
            res += bitArr[i];
        }
        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    TreeArr ta(n);
    for (int i = 1; i <= m; i++) {
        i64 ai;
        cin >> ai;
        ta.update(ai, 1);
    }
    i64 ans = 0;
    if (n % 2 == 1) {
        for (i64 i = 1; i <= n / 2; i++) {
            i64 leftlessnum  = ta.query(i - 1);
            i64 rightlessnum = ta.query(n - i - 1);
            i64 leftnum      = m - leftlessnum;
            i64 rightnum     = m - rightlessnum;
            ans += rightnum * (leftnum - 1) * 2;
        }
        cout << ans << '\n';
        return;
    } else {
        for (i64 i = 1; i < n / 2; i++) {
            i64 leftlessnum  = ta.query(i - 1);
            i64 rightlessnum = ta.query(n - i - 1);
            i64 leftnum      = m - leftlessnum;
            i64 rightnum     = m - rightlessnum;
            ans += rightnum * (leftnum - 1) * 2;
        }
        i64 num = m - ta.query(n / 2 - 1);
        ans += num * (num - 1);
        cout << ans << '\n';
        return;
    }
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
    // 首先，对于所有方案，都可以反转成为第二种
    // 1:n-1,2:n-2的方法是否可行？
    // 查询大于等于k的油漆数量可以做到log n，那么小于等于k的只要-1就都可组合对吧
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}