#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
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
    int         n;
    string      s, t;
    vector<int> tar(27);
    vector<int> indegree(27, 0);
    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) {
        int si = s[i] - 'a' + 1;
        int ti = t[i] - 'a' + 1;
        if (tar[si] == 0) {
            tar[si] = ti;
            indegree[ti]++;
        } else {
            if (tar[si] != ti) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }
    vector<bool>        vis(27, false);
    function<bool(int)> dfs = [&](int root) {
        if (root == 0) {
            return false;
        }
        vector<int> times(27);
        vector<int> path;
        while (root) {
            path.emplace_back(root);
            if (times[root] != 0) {
                if (!vis[root]) {
                    for (int i : path) {
                        vis[i] = true;
                    }
                    return true;
                }
                return false;
            }
            times[root]++;
            root = tar[root];
        }
        return false;
    };
    int cnt  = 0;
    int cnt3 = 0;
    for (int i = 1; i <= 26; i++) {
        if (tar[i] != 0) {
            if (tar[i] != i) {
                cnt3++;
                if (dfs(i)) {
                    cnt++;
                }
            }
        }
    }
    vis.assign(27, false);
    bool flag = false;
    for (int i = 1; i <= 26; i++) {
        if (indegree[i] == 0) flag = true;
    }
    if (flag)
        cout << cnt + cnt3;
    else
        cout << -1;
    return 0;
}