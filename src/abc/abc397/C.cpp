#include <set>
#include <vector>
#define REMOVE_ME
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
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    vector<int> pre(n + 1);
    vector<int> suf(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    set<int> cnt1;
    set<int> cnt2;
    for (int i = 1; i <= n; i++) {
        cnt1.insert(arr[i]);
        pre[i] = cnt1.size();
    }
    for (int i = n; i >= 1; i--) {
        cnt2.insert(arr[i]);
        suf[i] = cnt2.size();
    }
    int maxV = 0;
    for (int i = 1; i <= n - 1; i++) {
        maxV = max(maxV, suf[i] + pre[i - 1]);
    }
    cout << maxV;
    return 0;
}