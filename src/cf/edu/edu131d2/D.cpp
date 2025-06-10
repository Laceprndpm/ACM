#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           n;

struct node {
    i64 l;
    // i64 len;
    i64 r;
    i64 pos;

    bool operator<(node& t) const
    {
        return !(r < t.r);
    };
};

node getxandlen(int i, int bi)  //  bi = i / x == j
{
    if (bi == 0) {
        int lpoint = i + 1;
        return {lpoint, n, i};
    }
    int lpoint = (i == bi) ? 1 : 1 + (i / (bi + 1));
    int rpoint = (i >= lpoint) ? (i / (i / lpoint)) : n;
    return {lpoint, rpoint, i};
}

void solve()
{
    cin >> n;
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    priority_queue<node, vector<node>, less<>> pq;
    vector<vector<node>>                       addd(n + 1);

    for (int i = 1; i <= n; i++) {
        node cur = getxandlen(i, b[i]);
        addd[cur.l].emplace_back(cur);
    }
    vector<int> ans(n + 1);
    int         curn = 0;

    for (curn = 1; curn <= n; curn++) {
        // while (pq.top().l < curn) {
        //     node cur = pq.top();
        //     pq.pop();
        //     pq.push(cur);
        // }
        for (auto j : addd[curn]) {
            pq.push(j);
        }
        node cur = pq.top();
        pq.pop();
        ans[cur.pos] = curn;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

// 如果不为1或者2，比如说3，19/6 = 3， 19/5 = 3.
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