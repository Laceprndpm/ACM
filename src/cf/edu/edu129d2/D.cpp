#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = unsigned long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           n, x;

bool check(i64 x)
{
    i64 now = 1;
    for (int i = 1; i <= 18; i++) {
        if (x == now) return true;
        now *= 10;
    }
    return false;
}

i64 qpow(i64 n, i64 q)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
        }
        n *= n;
        q >>= 1;
    }
    return ans;
}

i64 tenLen(i64 x)
{
    i64 cur = 1;
    for (int i = 1;; i++) {
        cur *= 10;
        if (x < cur) {
            return i;
        }
    }
}

struct item {
    i64 losstime;
    i64 val;

    bool operator<(const item& other) const
    {
        return val < other.val;
    }
};

bool ok(i64 time)
{
    priority_queue<item, vector<item>, less<item>> pq;
    pq.push({0, x});
    while (!pq.empty()) {
        item cur = pq.top();
        if (tenLen(cur.val) >= n) {
            return true;
        }
        pq.pop();
        i64          val = cur.val;
        vector<bool> meet(10);
        meet[0] = true;
        while (val) {
            if (!meet[val % 10]) {
                meet[val % 10] = true;
                item temp{cur.losstime, cur.val * (val % 10)};
                if (tenLen(cur.val) == tenLen(cur.val * (val % 10))) {
                    temp.losstime++;
                }
                if (temp.losstime <= time) {
                    pq.push(temp);
                }
            }
            val /= 10;
        }
    }
    return false;
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
    cin >> n >> x;
    if (check(x)) {
        cout << -1 << '\n';
        return 0;
    }
    if (!ok(20)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 20; i >= 0; i--) {
        if (!ok(i)) {
            cout << i + n - tenLen(x) + 1;
            return 0;
        }
    }
    cout << n - tenLen(x);
    return 0;
}