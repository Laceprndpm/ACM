#include <functional>
#include <iostream>
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
    int n, k;
    cin >> n >> k;
    // 如果选择[v1, v2... vk]的值分别是[a1, a2, ... ak]
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    // 最大的k - 1个数以及末尾
    i64                                         sum = 0;
    priority_queue<i64, vector<i64>, greater<>> pq;
    int                                         i = 0;
    for (; i < k - 1; i++) {
        sum += arr[i];
        pq.push(arr[i]);
    }
    i64 ans = sum + arr[i] + i + 1;
    for (; i < n - 1; i++) {
        if (!pq.empty() && arr[i] > pq.top()) {
            sum -= pq.top();
            pq.pop();
            pq.push(arr[i]);
            sum += arr[i];
        }
        ans = max(ans, sum + i + 2 + arr[i + 1]);
    }
    cout << ans << '\n';
    return 0;
}