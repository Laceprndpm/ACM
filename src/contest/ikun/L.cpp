#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           n, p, q;

struct node {
    i64 x, y;

    bool operator<(const node& t) const
    {
        if (x != t.x) {
            return x < t.x;
        }
        return y > t.y;
    }
};

i64 work(const vector<node>& arr)
{
    node last{p, 0};
    i64  ans = 0;
    for (const node& i : arr) {
        ans += (last.x - i.x + 1) * (q - i.y + 1);
        last = i;
        last.x--;
        last.y--;
    }
    return ans;
}

void solve()
{
    cin >> n >> p >> q;
    vector<node> arr(n);
    // for (auto& i : arr) {
    //     cin >> i.x >> i.y;
    //     i.x++, i.y++;
    // }
    node ed{0, q + 1};
    for (int i = 0; i < n; i++) {
        cin >> arr[i].x >> arr[i].y;
        if (arr[i].x >= p || arr[i].y >= q) {
            i--;
            n--;
            continue;
        }
        arr[i].x++;
        arr[i].y++;
    }
    sort(arr.begin(), arr.begin() + n);
    node                 last{0, 0};
    vector<vector<node>> buffer(n + 1);
    int                  cnt = 0;
    i64                  ans = (q + p) * (p + 1) * (q + 1) / 2;
    vector<i64>          dp(n + 1, INF);
    i64                  mx = INF;
    for (int i = 0; i < n; i++) {
        auto up = lower_bound(dp.begin(), dp.begin() + n, arr[i].y);
        buffer[up - dp.begin()].emplace_back(arr[i]);
        *up  = arr[i].y;
        last = arr[i];
    }
    while (dp[cnt] != mx) {
        ++cnt;
    }
    for (int i = 0; i < cnt; i++) {
        sort(buffer[i].begin(), buffer[i].end(), [&](const node& a, const node& b) {
            if (a.x != b.x) {
                return a.x > b.x;
            }
            return a.y < b.y;
        });
        buffer[i].emplace_back(ed);
        i64 temp = work(buffer[i]);
        ans -= temp;
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