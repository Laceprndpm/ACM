#include <algorithm>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct ab {
    int a;
    int b;

    bool operator>(ab& t)
    {
        if (a != t.a)
            return a > t.a;
        else
            return b > t.b;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ab> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].a;
    }
    for (int i = 0; i < n; i++) {
        cin >> vec[i].b;
    }
    vector<ab> origin(vec);
    sort(vec.begin(), vec.end(), greater<>());
    for (int i = 0; i < n - 1; i++) {
        if (vec[i].b < vec[i + 1].b) {
            cout << -1 << '\n';
            return;
        }
    }
    int                    cnt = 0;
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (origin[j] > origin[j + 1]) {
                swap(origin[j], origin[j + 1]);
                ans.emplace_back(j + 1, j + 2);
                cnt++;
                if (cnt > 1e4) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto& i : ans) {
        cout << i.first << ' ' << i.second << '\n';
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