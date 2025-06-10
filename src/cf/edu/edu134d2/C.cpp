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
    vector<int> arr(n + 1);
    vector<int> brr(n + 1);
    vector<int> lb(n + 1);
    vector<int> ub(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> brr[i];
    }
    int p1 = n, p2 = n;
    do {
        while (p2 != 0 && brr[p2] >= arr[p1]) {
            p2--;
        }
        lb[p1] = p2 + 1;
    } while (--p1 >= 1);
    for (int i = n; i >= 1; i--) {
        if (i == n) {
            ub[n] = n;
        } else {
            if (lb[i + 1] == i + 1) {
                ub[i] = i;
            } else {
                ub[i] = ub[i + 1];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << brr[lb[i]] - arr[i] << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        cout << brr[ub[i]] - arr[i] << ' ';
    }
    cout << '\n';
}

//
// 4
// 10 20 30 40
// 22 33 33 55
// 4  4  3  1
// 1  1  2  4
// 3  3  3  4
//
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