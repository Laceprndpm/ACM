#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    // 即满足全体|为x，且使得a1,a2尽可能小的同时不重复？
    // 假如n == 1，只能x一个
    //
    //
    int n, x;
    cin >> n >> x;
    if (n == 1) {
        cout << x << '\n';
        return;
    }
    if (n == 2) {
        cout << x << ' ' << '0' << '\n';
        return;
    }
    // 先拆位，每一位一个，随后如果位数>n，则进行合成？直接全部合成掉，随后从最低位枚举是否更优？反例：11 = 1, 2
    // 1101，维护cur，如果队列头的大于等于cur，就可以把头给到队列尾的数
    //
    //
    deque<int> q;
    int        cnt = n;
    for (int i = 0; i < 30; i++) {
        if (x >> i & 1) {
            q.push_back(1 << i);
            cnt--;
        }
    }
    int cur = 0;
    while (cnt <= 0) {
        q.back() |= q.front();
        q.pop_front();
        cnt++;
    }
    while (cnt--) {
        cout << cur << ' ';
        cur++;
        if ((cur | x) != x) {
            cur--;
            for (int i = 0; i < cnt; i++) {
                cout << cur << ' ';
            }
            break;
        }
        if (!q.empty() && cur >= q.front()) {
            q.pop_front();
            cnt++;
        }
        if (cnt == 0) {
            if (q.size() > 1 && q.front() > cur) {
                q.back() |= q.front();
                q.pop_front();
                cnt++;
            }
        }
    }
    for (int i : q) {
        cout << i << ' ';
    }
    cout << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}