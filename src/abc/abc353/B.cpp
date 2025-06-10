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
    int n, k;
    cin >> n >> k;
    vector<int> group(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> group[i];
    }
    int cur = 0;
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (cur + group[i] > k) {
            cur = 0;
            cnt++;
        }
        cur += group[i];
    }
    cout << cnt << '\n';
    return 0;
}