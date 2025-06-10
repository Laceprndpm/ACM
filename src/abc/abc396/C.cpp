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
    int n, m;
    cin >> n >> m;
    vector<int> B(n + 1);
    vector<int> W(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> B[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> W[i];
    }
    sort(B.begin() + 1, B.end(), greater<int>());
    sort(W.begin() + 1, W.end(), greater<int>());
    i64 sum = 0;
    int i;
    for (i = 1; i <= min(n, m); i++) {
        if (W[i] < 0 || B[i] + W[i] < 0) {
            break;
        } else {
            sum += B[i] + W[i];
        }
    }

    for (; i <= n; i++) {
        if (B[i] < 0) {
            break;
        }
        sum += B[i];
    }
    cout << sum << '\n';
    return 0;
}