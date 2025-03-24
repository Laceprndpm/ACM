#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
int           n;

int getAx(int x)
{
    if (x >= n) {
        int m = x / 2;
        if (m % 2 == 1) {
            if (n % 2 == 1) {
                return prefix[n];
            } else {
                return prefix[n] + getAx(n + 1);
            }
        } else {
            if (n % 2 == 1) {
                return prefix[n] + getAx(n / 2);
            } else {
                return prefix[n] + getAx(n + 1) + getAx(n / 2);
            }
        }
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
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> input(l + 1);
    for (int i = 1; i <= n; i++) {
        cin >> input[i];
    }
    int cur = 0;
    for (int i = 1; i <= l; i++) {
        cur ^= input[i];
        if (i * 2 > n && i * 2 < l) {
            input[i * 2] = cur;
        }
        if (i * 2 + 1 > n && i * 2 + 1 < l) {
            input[i * 2 + 1] = cur;
        }
        cout << input[i] << ' ';
        if (!(i % n)) {
            cout << '\n';
        }
    }
    return 0;
}

// 11 10 9 ... 5 4 3 2 1