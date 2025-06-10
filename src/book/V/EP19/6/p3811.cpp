#include <iostream>
#include <vector>
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
    i64 n, p;
    cin >> n >> p;
    vector<i64> arr(n + 1);
    arr[1] = 1;
    for (int i = 2; i <= n; i++) {
        arr[i] = (-arr[(p % i)] * (p / i) % p + p) % p;
    }
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << '\n';
    }
    return 0;
}