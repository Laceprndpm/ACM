#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           n, k;

bool check(vector<int>& arr)
{
    vector<int>  prefix(n + 1);
    vector<int>  okpre(n + 1);
    vector<int>  weight(n + 1);
    vector<int>  okdiff(n + 1);
    vector<int>  prefixMin(n + 1);
    vector<int>  prefixMax(n + 1);
    vector<bool> okMid(n + 1);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        if (arr[i] <= k) {
            prefix[i + 1]++;
        }
        if (prefix[i + 1] * 2 >= (i + 1)) {
            okpre[i + 1] = true;
        }
        okpre[i + 1] |= okpre[i];
        weight[i]        = prefix[i + 1] * 2 - i;
        prefixMin[i + 1] = min(prefixMin[i], weight[i]);
        if (weight[i] - prefixMin[i] >= 0) {
            okMid[i] = true;
        }
    }

    int cntK = 0;
    for (int i = n - 1; i >= 2; i--) {
        if (arr[i] <= k) {
            cntK++;
        }
        if (cntK * 2 >= n - i) {
            if (okpre[i] || okMid[i - 1]) {
                return true;
            }
        }
    }
    return false;
}

void solve()
{
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (check(arr)) {
        cout << "Yes\n";
        return;
    } else {
        reverse(arr.begin(), arr.end());
        if (check(arr)) {
            cout << "Yes\n";
            return;
        } else {
            cout << "No\n";
            return;
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}