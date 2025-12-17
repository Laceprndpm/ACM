#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class TreeArr {
private:
    vector<int> bitArr;
    vector<int> stk;

    int lowbit(int x) { return x & -x; }

public:
    TreeArr(int size) : bitArr(size) {}

    void update(int place, int value)
    {
        assert(place > 0);
        stk.push_back(place);
        for (int i = place; i < (int)bitArr.size(); i += lowbit(i)) {
            bitArr[i] += value;
        }
    }

    void updateBt(int place, int value)
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

    void clear()
    {
        for (int i : stk) {
            updateBt(i, -1);
        }
        stk.clear();
    }
} tr((int)1e6 + 1);

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    set<int> xi, yi;
    for (int i = 0; i < n; i++) {
        int curXi;
        cin >> curXi;
        xi.insert(curXi);
    }
    xi.insert(0), xi.insert((int)1e6);
    for (int i = 0; i < m; i++) {
        int curYi;
        cin >> curYi;
        yi.insert(curYi);
    }
    yi.insert(0), yi.insert((int)1e6);
    i64                    ans = 0;
    vector<pair<int, int>> xq, yq;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        if (xi.count(x) && yi.count(y)) {
            continue;
        }
        if (xi.count(x)) {
            xq.push_back({x, y});
        } else {
            yq.push_back({x, y});
        }
    }
    sort(xq.begin(), xq.end());
    sort(yq.begin(), yq.end(), [&](const pair<int, int>& x, const pair<int, int>& y) {
        if (x.second == y.second) {
            return x.first < y.first;
        }
        return x.second < y.second;
    });
    {
        tr.clear();
        vector<int> y_toadd;
        for (auto iter = xq.begin(); iter != xq.end(); iter++) {
            if (iter != xq.begin() && prev(iter)->first != iter->first) {
                for (int i : y_toadd) {
                    tr.update(i, 1);
                }
                y_toadd.clear();
            }
            auto [x, y] = *iter;
            auto it     = yi.lower_bound(y);
            int  r      = *it;
            int  l      = *prev(it);
            ans += tr.query(r) - tr.query(l);
            y_toadd.push_back(y);
        }
    }
    {
        tr.clear();
        vector<int> x_toadd;
        for (auto iter = yq.begin(); iter != yq.end(); iter++) {
            if (iter != yq.begin() && prev(iter)->second != iter->second) {
                for (int i : x_toadd) {
                    tr.update(i, 1);
                }
                x_toadd.clear();
            }
            auto [x, y] = *iter;
            auto it     = xi.lower_bound(x);
            int  r      = *it;
            int  l      = *prev(it);
            ans += tr.query(r) - tr.query(l);
            x_toadd.push_back(x);
        }
    }
    cout << ans << '\n';
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