#include <algorithm>
#include <functional>
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
    int n, q;
    cin >> n >> q;
    vector<i64> input(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> input[i];
    }
    sort(input.begin() + 1, input.begin() + n + 1, greater<i64>());
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix[i] = input[i] + prefix[i - 1];
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << prefix[x] - prefix[x - y] << '\n';
    }
    return 0;
}