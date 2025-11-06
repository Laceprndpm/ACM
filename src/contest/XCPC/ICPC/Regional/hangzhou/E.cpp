#include <functional>
#include <queue>
#include <stack>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct node {
    i64 l, r;
    i64 idx;

    bool operator<(node& t)
    {
        return !(l < t.l);
    }
};

void solve()
{
    i64 n, f;
    cin >> n >> f;
    vector<node> arr;
    i64          ans = 0;
    for (int i = 1; i <= n; i++) {
        i64 l, r;
        cin >> l >> r;
        arr.emplace_back(l, r, i);
    }
    priority_queue<node, vector<node>, less<>> pq(arr.begin(), arr.end());
    stack<node>                                st;
    vector<i64>                                ansidx;
    while (!pq.empty()) {
        while (!pq.empty() && pq.top().r <= f) {
            st.push(pq.top());
            pq.pop();
        }
        if (!pq.empty()) {
            auto [l, r, idx] = pq.top();
            pq.pop();
            ansidx.emplace_back(idx);
            ans += r - min(f, l);
            f = r;
        }
    }
    while (!st.empty()) {
        auto [l, r, idx] = st.top();
        st.pop();
        ans += r - l;
        ansidx.emplace_back(idx);
    }
    cout << ans << '\n';
    for (int i : ansidx) {
        cout << i << ' ';
    }
    cout << '\n';
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