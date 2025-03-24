#include <deque>
#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    const int   ok = k;
    vector<int> ai(n);
    vector<int> bi(n);
    for (int &i : ai) {
        cin >> i;
    }
    for (int &i : bi) {
        cin >> i;
    }
    vector<i64> nai(n * 2);
    for (int i = 0; i < n; i++) {
        nai[i] = ai[i];
    }
    for (int i = 0; i < n; i++) {
        nai[i + n] = ai[i];
    }
    for (int i = 0; i < n; i++) {
        nai[i] -= bi[i];
    }
    for (int i = 0; i < n; i++) {
        nai[i + n] -= bi[i];
    }

    function<bool(int)> check = [&](int x) {
        i64 len = 0;
        i64 sum = 0;
        k       = ok;
        deque<i64> dq;
        for (int i = 0; i < 2 * n; i++) {
            while (!dq.empty() && sum <= 0) {
                sum -= dq.front();
                dq.pop_front();
                len--;
            }
            sum += nai[i];
            len++;
            dq.emplace_back(nai[i]);
            while (!dq.empty() && sum <= 0) {
                sum -= dq.front();
                dq.pop_front();
                len--;
            }
            if (len + 1 > x) {
                if (sum <= k) {
                    k -= sum;
                    nai[i] -= sum;
                    dq.back() -= sum;
                    if (i < n) {
                        nai[n + i] -= sum;
                    }
                    sum = 0;
                } else {
                    return false;
                }
            }
        }
        return true;
    };
    int l = 0, r = n;
    while (l < r) {
        int mid = (r - l) / 2 + l;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    //
    // 2 1 1 2
    // 1 2 2 1
    //
    //
    //
    // 枚举左端点，往右找右端点，第一个使得区间1的和小于等于区间2的右端点，长度越长越好
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}