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

// class SegmentTree {
// private:
//     vector<i64> left, right;
//     vector<i64> leftSon, rightSon;
//     i64         cnt = 1;
//     vector<i64> val;
//     i64         __n;

//     void update(i64 root, i64 idx, i64 value)
//     {
//         i64 l = left[root], r = right[root];
//         if (l == r) {
//             val[root] = value;
//             return;
//         }
//         i64 mid = (l + r) >> 1;
//         if (idx <= mid) {
//             if (leftSon[root] == -1) {
//                 leftSon[root] = ++cnt;
//                 leftSon.emplace_back(-1);
//                 rightSon.emplace_back(-1);
//                 val.emplace_back(0);
//                 left.emplace_back(l);
//                 right.emplace_back(mid);
//             }
//             update(leftSon[root], idx, value);
//         } else {
//             if (rightSon[root] == -1) {
//                 rightSon[root] = ++cnt;
//                 rightSon.emplace_back(-1);
//                 leftSon.emplace_back(-1);
//                 val.emplace_back(0);
//                 left.emplace_back(mid + 1);
//                 right.emplace_back(r);
//             }
//             update(rightSon[root], idx, value);
//         }
//         val[root] = (val[leftSon[root]] + val[rightSon[root]]);
//     }

//     i64 quary(i64 root, i64 start, i64 end)
//     {
//         if (val[root] == 0) {
//             return 0;
//         }
//         if (start > right[root] || end < left[root]) {
//             return 0;
//         }
//         i64 l = left[root], r = right[root];
//         if (start <= l && r <= end) {
//             return val[root];
//         }
//         i64 sum = 0;
//         if (leftSon[root] != -1) {
//             sum += quary(leftSon[root], start, end);
//         }

//         if (rightSon[root] != -1) {
//             sum += quary(rightSon[root], start, end);
//         }
//         return sum;
//     }

// public:
//     SegmentTree(i64 n) : left(2), right(2), leftSon(2, 0), rightSon(2, 0), val(2, 0), __n(n)
//     {
//         left[cnt]  = 0;
//         right[cnt] = n;
//     }

//     void update(i64 idx, i64 value)
//     {
//         if (idx > __n) {
//             perror("Index out of bound.(SegmentTree->update)");
//             throw exception();
//         }
//         update(1, idx, value);
//     }

//     i64 quary(i64 l, i64 r)
//     {
//         if (l > r) {
//             perror("\"l\" could not larger than \"r\".(SegmentTree->quary)");
//             throw exception();
//         }
//         if (l < 0 || r > __n) {
//             perror("Index out of bound.(SegmentTree->quary)");
//             throw exception();
//         }
//         return quary(1, l, r);
//     }
// };

class TreeArr {
private:
    vector<int> bitArr;
    vector<int> stk;

    int lowbit(int x)
    {
        return x & -x;
    }

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