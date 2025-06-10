#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int q;
    cin >> q;
    // DSU                   dsu(5e5 + 5);
    vector<array<int, 3>> arr(q);
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        int x, y = -1;
        if (cmd == 1) {
            cin >> x;
        } else {
            cin >> x >> y;
        }
        arr[i] = {cmd, x, y};
    }
    vector<int> ans;
    ans.reserve(q);
    vector<vector<int>> rerout((int)5e5 + 50);
    vector<int>         to((int)5e5 + 50);
    vector<int>         dto((int)5e5 + 50);
    vector<int>         inTime((int)5e5 + 50, INF);
    vector<int>         outTime((int)5e5 + 50, INF);
    iota(to.begin(), to.end(), 0);

    for (int i = q - 1; i >= 0; i--) {
        if (arr[i][0] == 1) {
            ans.push_back(to[arr[i][1]]);
        } else {
            int u = arr[i][1], v = arr[i][2];
            int curT  = i;
            int lastv = -1;
            while (v != to[v] && inTime[v] >= curT) {
                if (lastv != -1) {
                    to[lastv]      = to[v];
                    outTime[lastv] = inTime[v];
                }
                lastv = v;
                curT  = outTime[v];
                v     = to[v];
            }
            to[u]      = v;
            inTime[u]  = i;
            outTime[u] = curT;
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

//  6
//  1 8
//  2 8 7
// 7
//  2 7 3
// 3
//  2 5 9
// 3
//  2 9 4
// 3
//  2 3 5
// 5

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}