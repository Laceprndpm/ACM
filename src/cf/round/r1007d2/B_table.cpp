#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

bool isSqaure(i64 x)
{
    i64 root = sqrt(x);
    if (root * root == x) {
        return true;
    } else {
        return false;
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
    for (i64 i = 1; i <= 5e5; i++) {
        if (isSqaure((i + 1) * i / 2)) {
            cout << i << '\n';
        }
    }
    return 0;
}