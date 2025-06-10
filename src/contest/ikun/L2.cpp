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
        return y < t.y;
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
    node         last{0, 0};
    node         ed{0, q + 1};
    vector<node> buffer;
    i64          ans = (q + p) * (p + 1) * (q + 1) / 2;
    for (int j = 0; j < n; j++) {
        auto i = arr[j];
        if (i.y < last.y) {
            buffer.push_back(ed);
            ans -= work(buffer);
            buffer.clear();
        }
        buffer.push_back(i);
        last = i;
    }
    buffer.push_back(ed);
    ans -= work(buffer);
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