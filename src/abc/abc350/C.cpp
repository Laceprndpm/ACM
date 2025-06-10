#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
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
    int n;
    cin >> n;
    vector<int>            orgin(n + 1);
    vector<int>            place2val(n + 1);
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++) {
        cin >> orgin[i];
        place2val[orgin[i]] = i;
    }

    for (int i = 1; i < n; i++) {
        if (orgin[i] != i) {
            place2val[orgin[i]] = place2val[i];
            ans.push_back({i, place2val[i]});
            swap(orgin[i], orgin[place2val[i]]);
        }
    }
    cout << ans.size() << '\n';
    for (auto&& [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
    return 0;
}