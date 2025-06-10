#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct point {
    int x, y;

    int dist() const
    {
        if (x % 3 == 2 && y % 3 == 2) {
            return y + x + 2;
        } else {
            return x + y;
        }
    }

    bool operator<(const point& t) const
    {
        if (dist() != t.dist()) {
            return dist() > t.dist();
        } else if (x != t.x) {
            return x > t.x;
        } else {
            return y > t.y;
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    priority_queue<point, vector<point>, less<>> pq_Emtpy;
    priority_queue<point, vector<point>, less<>> pq_Not;
    int                                          x    = 0;
    function<void()>                             addT = [&](void) {
        for (int i = 0; i < x; i++) {
            pq_Emtpy.push({i * 3 + 1, x * 3 + 1});
            pq_Emtpy.push({x * 3 + 1, i * 3 + 1});
        }
        pq_Emtpy.push({x * 3 + 1, x * 3 + 1});
        x++;
    };
    vector<point> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        int ti;
        cin >> ti;
        if (pq_Emtpy.empty() || pq_Emtpy.top() < point{1, x * 3 + 1}) {
            addT();
        }
        if (ti == 1) {
            if (pq_Not.empty()) {
                auto cur = pq_Emtpy.top();
                pq_Emtpy.pop();
                pq_Not.push(cur);
                pq_Not.push({cur.x + 1, cur.y});
                pq_Not.push({cur.x, cur.y + 1});
                pq_Not.push({cur.x + 1, cur.y + 1});
            }
            auto cur1 = pq_Not.top();
            auto cur2 = pq_Emtpy.top();
            if (cur1 < cur2) {
                auto cur = pq_Emtpy.top();
                pq_Emtpy.pop();
                pq_Not.push(cur);
                pq_Not.push({cur.x + 1, cur.y});
                pq_Not.push({cur.x, cur.y + 1});
                pq_Not.push({cur.x + 1, cur.y + 1});
            }
            ai[i] = pq_Not.top();
            pq_Not.pop();
        } else {
            ai[i]    = pq_Emtpy.top();
            auto cur = pq_Emtpy.top();
            pq_Not.push({cur.x + 1, cur.y});
            pq_Not.push({cur.x, cur.y + 1});
            pq_Not.push({cur.x + 1, cur.y + 1});
            pq_Emtpy.pop();
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ai[i].x << ' ' << ai[i].y << '\n';
    }
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