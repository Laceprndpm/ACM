#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

class TreeArr {
private:
    vector<int> bitArr;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    TreeArr(int n) : bitArr(n) {}

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
    int n;
    cin >> n;
    vector<i64> arrI(n + 1);
    vector<i64> arrJ(n + 1);
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arrI[i];
    }
    for (int j = 1; j <= n; j++) {
        cin >> arrJ[j];
    }
    for (int j = 1; j <= n; j++) {
        prefix[j] = prefix[j - 1] + arrJ[j];
    }
    TreeArr     tomb(n + 5);
    vector<i64> remain(n + 1);
    for (int i = 1; i <= n; i++) {
        i64 cur = arrI[i];
        cur += prefix[i - 1];
        auto place = upper_bound(prefix.begin(), prefix.end(), cur);
        i64  idx   = place - prefix.begin();
        if (idx <= n) {
            tomb.update(idx, 1);
            remain[idx] += cur - prefix[idx - 1];
        }
    }
    for (int j = 1; j <= n; j++) {
        i64 ans = arrJ[j] * (j - tomb.query(j));
        ans += remain[j];
        cout << ans << ' ';
    }
    cout << '\n';
    return;
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