#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
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
    TreeArr(int size) : bitArr(size) {}

    void update(int place, int value)
    {
        assert(place > 0);
        for (int i = place; i < (int)bitArr.size(); i += lowbit(i)) {
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

i64 ct(vector<int>& t)
{
    int     n = t.size();
    TreeArr tr(n * 2 + 10);
    i64     ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += tr.query(t[i]);
        tr.update(t[i], 1);
    }
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> odd, even;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        if (i % 2 == 1) {
            odd.push_back(cur);
        } else {
            even.push_back(cur);
        }
    }
    i64 n1 = ct(odd);
    i64 n2 = ct(even);

    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    if ((n1 + n2) % 2 == 1) {
        if (n % 2 == 1)
            swap(*odd.rbegin(), *(odd.rbegin() + 1));
        else
            swap(*even.rbegin(), *(even.rbegin() + 1));
    }
    // cout << n1 << '\n';
    // cout << n2 << '\n';
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            cout << odd[(i - 1) / 2];
        } else {
            cout << even[(i - 1) / 2];
        }
        cout << ' ';
    }
    cout << '\n';
}

// 5 4 2 1 3
// 2 1 5 4 3
//
// 5 4 2 1 3
//
//
// 5 4 3 1 2
// 5 1 2 4 3 -1 -1
//
// 2 4 5 1 3 -1 +1
//
// 2 1 3 4 5 -1 -1
//
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