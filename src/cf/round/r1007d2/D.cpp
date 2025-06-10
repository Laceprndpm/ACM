#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
i64           n;
vector<bool>  prefix;
vector<int>   input;

int getAx(i64 x)
{
    if (x > n) {
        i64 m = x / 2;
        if (m <= n) return prefix[m];

        if (m % 2 == 1) {      // 11 10 ...
            if (n % 2 == 1) {  // n为奇数，即5,4[3,2,1]
                return prefix[n];
            } else {  // 即5,4,3,[2,1]
                return prefix[n] ^ getAx(n + 1);
            }
        } else {  // 10, 9...
            if (n % 2 == 1) {
                return prefix[n] ^ getAx(m);
            } else {
                return prefix[n] ^ getAx(n + 1) ^ getAx(m);
            }
        }
    } else {
        return input[x];
    }
}

void solve()
{
    i64 l, r;
    cin >> n >> l >> r;
    input.resize(n + 1);
    prefix.resize(n + 1);

    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> input[i];
    }
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] ^ input[i];
    }
    cout << getAx(l) << '\n';
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