#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    i64         k  = 0;
    i64         ak = 0;
    i64         a  = 0;
    vector<int> arr;
    int         last = 1;
    i64         sum  = 0;
    vector<int> brr(n + 1);
    for (int i = 1; i <= n; i++) {
        i64 cur;
        cin >> cur;
        brr[i] = cur;
        if (last * cur > 0) {
            sum += cur;
        } else {
            arr.emplace_back(sum);
            last = -1 * last;
            sum  = cur;
        }
    }
    arr.emplace_back(sum);
    for (i64 cur : arr) {
        ak += cur;
        if (ak < k) {
            ak = k;
        }
        if (a >= ak) {
            k  = a;
            ak = a;
        }
        a += cur;
    }
    // cout << k << '\n';
    i64 total = 0;
    int ache  = 0;
    for (int i = 1; i <= n; i++) {
        if (total >= k) {
            ache = true;
        }
        int a = brr[i];
        total += a;
        if (total < k && ache) {
            total = k;
        }
    }
    cout << total;
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
    // 假如选定k0，那么找到最后一个大于k的点
    // int t;
    // cin >> t;
    // while (t--) {
    solve();
    // }
    return 0;
}