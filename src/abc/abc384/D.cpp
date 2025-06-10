#include <iostream>
#include <numeric>
#include <queue>
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
    i64 n, sm;
    cin >> n;
    cin >> sm;
    vector<int> arr(n);
    for (auto& i : arr) {
        cin >> i;
    }
    i64 total = accumulate(arr.begin(), arr.end(), 0LL);
    sm %= total;
    i64        cur = 0;
    queue<i64> q;
    for (int i = 0; i < 2 * n; i++) {
        q.push(arr[i % n]);
        cur += arr[i % n];
        while (cur > sm) {
            cur -= q.front();
            q.pop();
        }
        if (cur == sm) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}