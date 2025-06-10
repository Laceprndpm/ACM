#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> idx_arr(n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cur--;
        idx_arr[cur].push_back(i);
    }
    set<int> st;
    // int      cnt = n - 1;
    i64                    ans = 0;
    vector<pair<int, int>> ap(n);
    for (int i = n - 1; i >= 0; i--) {
        for (int son : idx_arr[i]) {
            st.insert(son);
        }
        if (st.size() >= 2) {
            ans += *st.rbegin() - *st.begin();
            ap[i]    = {*st.begin(), *st.rbegin()};
            auto it1 = st.begin();
            auto it2 = st.end();
            it2--;
            st.erase(it1);
            st.erase(it2);
        } else {
            ap[i] = {-1, -1};
        }
    }
    int                 cnt = 0;
    set<int>            sgr;
    set<int, greater<>> sgl;
    for (int i = 0; i < n; i++) {
        if (ap[i].first == -1) {
            cnt++;
        } else if (cnt) {
            sgl.insert(ap[i].first);
            sgr.insert(ap[i].second);
            int lgap = ap[i].first - *sgr.begin();
            int rgap = *sgl.begin() - ap[i].second;
            if (max(lgap, rgap) > 0) {
                if (lgap >= rgap) {
                    ans += lgap * 2;
                    // sgr.erase(sgr.begin());
                    cnt--;
                } else {
                    ans += rgap * 2;
                    // sgl.erase(sgl.begin());
                    cnt--;
                }
                if (cnt == 0) {
                    sgr.clear();
                    sgl.clear();
                }
            }
        }
    }
    cout << ans << '\n';
}

// 假如我从小到大枚举
// 如果cnt[i] == 2
// 那么我只能填i吗？
// 不
// 1 1 2 2
// 最优为
// 1 1 1 1
//
// 为什么？
// 当我处理完所有为i-1的时，获得了一个l和r，莫非优先扩大现有的？
// 不，不一定
// 2 1 2 1 2 + 2 = 4
// 2 1 1 2
// 但是如果
// 2 1 1
// 那么明显只有一种选择，为什么？
// 3 4 1 1
// 3 1 1 4
//
// 3 1 4 1
// 反悔吗？
// 怎么反悔?
// 怎么贪心？
//
// 3 2 1 2 3
//
//
//

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