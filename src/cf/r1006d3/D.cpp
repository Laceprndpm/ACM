#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    int ansL, ansR;
    int ans = INT32_MIN;
    for (int l = 0; l < n; l++) {
        int cntLess  = 0;
        int cntGreat = 0;
        for (int i = l; i < n; i++) {
            if (arr[i] > arr[l]) {
                cntGreat++;
            } else if (arr[i] < arr[l]) {
                cntLess++;
            }
            if (ans < cntLess - cntGreat) {
                ans  = cntLess - cntGreat;
                ansL = l, ansR = i;
            }
        }
    }
    cout << ansL + 1 << ' ' << ansR + 1 << '\n';
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
    // 对于l前,r后的数组，l-r中的变换不会影响
    // 对于给定lr，每次减少了l-r内cnt|a<al，增加cnt|a>ar
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}