#include <deque>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct point {
    int x, y;

    bool operator<(point& t) const
    {
        if (x == t.x) {
            return y < t.y;
        }
        return x < t.x;
    }

    friend ostream& operator<<(ostream& os, const point& x)
    {
        os << x.x << ' ' << x.y;
        return os;
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
    int n;
    cin >> n;
    set<point>           mp;
    vector<point>        inp;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mp.insert({x, y});
        inp.emplace_back(x, y);
    }
    vector<int>               dx{0, 0, -1, 1};
    vector<int>               dy{-1, 1, 0, 0};
    deque<pair<point, point>> que;
    for (auto i : mp) {
        for (int j = 0; j < 4; j++) {
            if (mp.count({i.x + dx[j], i.y + dy[j]}) == 0) {
                que.push_back({{i.x + dx[j], i.y + dy[j]}, {i.x + dx[j], i.y + dy[j]}});
            }
        }
    }
    map<point, point> dist;
    while (!que.empty()) {
        auto [cur, dis] = que.front();
        que.pop_front();
        for (int i = 0; i < 4; i++) {
            point nxt = {cur.x + dx[i], cur.y + dy[i]};
            if (mp.contains(nxt) && !dist.contains(nxt)) {
                dist[nxt] = dis;
                que.push_back({nxt, dis});
            }
        }
    }
    for (auto i : inp) {
        cout << dist[i] << '\n';
    }
    return 0;
}