#include <utility>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int mydfs(pair<int, int> l, pair<int, int> r, int j)  // l和r和处理到了2的几次方
{
    int a      = (l.first + (1 << j) - 1) / (1 << j);
    int b      = (r.first + (1 << j) - 1) / (1 << j);
    int block1 = (l.second - a * (1 << j)) / (1 << j);
    int block2 = (r.second - b * (1 << j)) / (1 << j);
    l.second -= block1 * (1 << j);
    r.second -= block2 * (1 << j);
    pair<int, int> a1{l.first, l.second};
    pair<int, int> a2{l.first, l.second};
    pair<int, int> b1{r.first, b * (1 << j)};
    pair<int, int> b2{(b + block2) * (1 << j), r.second};
    pair<int, int> a3{l.first, a * (1 << j)};
    pair<int, int> b3{b * (1 << j), (b + block2) * (1 << j)};

    pair<int, int> a4{(a + block1) * (1 << j), l.second};
    pair<int, int> b4{b * (1 << j), (b + block2) * (1 << j)};
    if (j != 0)
        return mydfs(a1, b1, j - 1) + mydfs(a2, b2, j - 1) + mydfs(a3, b3, j - 1) + mydfs(a3, b3, j - 1)
               + block1 * block2;
    else
        return block1 * block2;
}

void solve()
{
    pair<int, int> l;
    pair<int, int> r;
    cin >> l.first >> l.second >> r.first >> r.second;
    cout << mydfs(l, r, 5) << '\n';
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