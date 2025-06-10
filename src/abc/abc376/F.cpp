#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
    map<pair<int, int>, int>               cur;
    map<pair<int, int>, int>               nxt;
    function<int(int st, int ed, int mid)> dontMove = [&](int st, int ed, int mid) -> int {
        st = (n + st - mid) % n;
        ed = (n + ed - mid) % n;
        return abs(st - ed);
    };
    function<tuple<int, int>(int st, int ed, int mid)> needMove = [&](int st, int ed, int mid) -> tuple<int, int> {
        if (st == ed) {
            return {mid, 0};
        }
        if (st < ed) {
            if (mid > ed)
                st += n;
            else if (mid < st)
                ed -= n;
        } else if (st > ed) {
            if (mid < ed)
                st -= n;
            else if (mid > st)
                ed += n;
        }
        if (st < mid && mid <= ed) {
            int cost = ed - st + ed + 1 - mid;
            int temp = ed + 1;
            temp %= n;
            temp += n;
            temp %= n;
            if (temp == 0) {
                temp = n;
            }
            return {temp, cost};
        }
        if (st > mid && mid >= ed) {
            int cost = st - ed + (mid + 1 - ed);
            int temp = ed - 1;
            temp %= n;
            temp += n;
            temp %= n;
            if (temp == 0) {
                temp = n;
            }
            return {temp, cost};
        } else {
            assert(0);
        }
    };
    cur[{1, 2}]                         = 0;
    function<void(int, int, int)> try_p = [&](int l, int r, int v) -> void {
        if (nxt.count({l, r}) == 0) {
            nxt[{l, r}] = v;
        } else {
            nxt[{l, r}] = min(nxt[{l, r}], v);
        }
    };
    while (q--) {
        char cmd;
        cin >> cmd;
        int target;
        cin >> target;
        if (cmd == 'L') {
            for (const auto& [key, c] : cur) {
                auto [l, r] = key;
                int c1      = dontMove(l, target, r);
                if (target != r) try_p(target, r, c1 + c);
                auto [md, c2] = needMove(l, target, r);
                try_p(target, md, c2 + c);
            }
        } else {
            for (const auto& [key, c] : cur) {
                auto [l, r] = key;
                int c1      = dontMove(r, target, l);
                if (target != l) try_p(l, target, c1 + c);
                auto [md, c2] = needMove(r, target, l);
                try_p(md, target, c2 + c);
            }
        }
        cur = nxt;
        nxt.clear();
    }
    int ans = INF;
    for (auto [key, val] : cur) {
        ans = min(ans, val);
    }
    cout << ans << '\n';
    return 0;
}