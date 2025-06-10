#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

// 可以明显观察到，如果一个连续
// 非零子序列含有2，则填那一个2
// ，其他不管则最优
// 否则，如果这个字段左面已经没
// 有可变红的，优先让左变红，反
// 之让右
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            if (i + 1 >= n || arr[i + 1] == '0') {
                ans++;
            } else {
                i++;
                bool doublearrow = false;
                while (arr[i] != 0 && i < n) {
                    if (arr[i] == 2) {
                        doublearrow = true;
                    }
                    i++;
                }
                if (!doublearrow) {
                    i--;
                }
                ans++;
                doublearrow = false;
            }
        } else {
            while (arr[i] != 0 && i < n) {
                i++;
            }
            ans += 1;
        }
    }
    cout << ans << endl;
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}

// 2 1 0 0 1
// 0 1 2 3 4