#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <ranges>
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
    TreeArr(int size) : bitArr(size + 1) {}

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

    bool check(int l, int r)
    {
        if (l == 0) return query(r) != 0;
        return query(r) - query(l - 1) != 0;
    }
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    TreeArr tr(n + 1);
    string  s;
    cin >> s;
    vector<int> prefix1(n + 1);
    vector<int> suffix2(n + 1);
    for (int i = 0; i < n; i++) {
        prefix1[i + 1] = prefix1[i] + (s[i] == '1' ? 1 : 0);
    }
    for (int i = n - 1; i >= 0; i--) {
        suffix2[i] = suffix2[i + 1] + (s[i] == '2' ? 1 : 0);
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '/') {
            tr.update(i + 1, 1);
        }
    }
    int        l, r;
    const auto check = [&](const int x) -> bool {
        int  need1 = x + prefix1[l];
        int  need2 = x + suffix2[r + 1];
        auto liter = lower_bound(prefix1.begin() + 1, prefix1.end(), need1);
        auto riter = lower_bound(suffix2.rbegin() + 1, suffix2.rend(), need2);
        if (liter == prefix1.end() || riter == suffix2.rend()) {
            return false;
        }
        int lidx = distance(prefix1.begin(), liter) - 1;
        int ridx = distance(riter, suffix2.rend()) - 1;
        if (lidx <= ridx && tr.check(lidx + 1, ridx + 1)) {
            return true;
        } else {
            return false;
        }
    };
    while (q--) {
        cin >> l >> r;
        l--, r--;

        if (tr.check(l + 1, r + 1)) {
            auto num = ranges::views::iota(0, (r - l + 1) / 2 + 1);
            auto res = *partition_point(num.begin(), num.end(), check);
            cout << res * 2 + 1 - 2 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}