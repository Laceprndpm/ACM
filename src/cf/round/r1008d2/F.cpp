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
    // cnt0 in n
    // for j + i in range(n)
    // for i : C(cnt0, i) * C(cnt1, j) * F(i - j)
    // a = j + i
    // b = i - j
    // for a in range n
    // for (a - b) / 2 : C(cnt0, b) * [(a + b) / 2 : C(cnt1, $)] * F(b)
    return 0;
}