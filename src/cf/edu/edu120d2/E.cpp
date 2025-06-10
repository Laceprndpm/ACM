#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

ostream& operator<<(ostream& os, const vector<int>& vec)
{
    for (int i : vec) {
        cout << i + 1 << ' ';
    }
    return os;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> expected(n);
    for (int& i : expected) {
        cin >> i;
    }
    vector<string> stu(n);
    vector<int>    val(m);
    for (string& i : stu) {
        cin >> i;
    }
    int         nb = (1 << n) - 1;
    vector<int> p(m);
    vector<int> good;
    iota(p.begin(), p.end(), 0);
    i64 ans = -1;
    for (int ib = 0; ib <= nb; ib++) {  // 1为正
        i64 cur = 0;
        val.assign(m, 0);                  // 每次贡献要清空
        for (int k = 0; k < n; k++) {      // 枚举人
            for (int j = 0; j < m; j++) {  // 枚举问题
                if (stu[k][j] == '1') {    // 答对了
                    val[j] += ((ib >> k & 1) ? 1 : -1);
                }
            }
            cur += ((ib >> k & 1) ? 1 : -1) * -1 * expected[k];  // 和前者相反
        }
        sort(p.begin(), p.end(), [&](int x, int y) {
            return val[x] < val[y];
        });
        for (int j = 0; j < m; j++) {
            cur += val[p[j]] * (j + 1);
        }
        if (cur > ans) {
            ans  = cur;
            good = p;
        }
    }
    vector<int> ansvec(m);
    for (int i = 0; i < m; i++) {
        ansvec[good[i]] = i;
    }
    cout << ansvec << '\n';
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

// i64 cur = std::accumulate(std::views::zip(val, p).begin(), std::views::zip(val, p).end(), 0,
//                           [](int sum, const auto& pair) {
//                               auto [a, b] = pair;
//                               return sum + a * b;
//                           });