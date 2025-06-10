#include <iostream>
#include <queue>
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
    int n, k;
    cin >> n >> k;
    if (n < k) {
        cout << 1 << '\n';
        return 0;
    }
    i64        sum = k;
    queue<i64> que;
    int        i;
    for (i = 0; i < k; i++) {
        que.push(1);
    }
    for (; i < n; i++) {
        que.push(sum);
        sum += sum;
        sum -= que.front();
        sum += (int)1e9;
        sum %= (int)1e9;
        que.pop();
    }
    cout << sum << '\n';
    return 0;
}