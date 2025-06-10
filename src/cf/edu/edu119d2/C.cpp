#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, k, x;
    cin >> n >> k >> x;
    x--;
    string s;
    cin >> s;
    vector<int> pos;
    int         cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '*') {
            cnt++;
        } else {
            if (cnt != 0) pos.push_back(cnt * k + 1);
            cnt = 0;
        }
    }
    if (cnt != 0) pos.push_back(cnt * k + 1);
    cnt = 0;
    deque<i64> ans;
    for (auto it = pos.rbegin(); it != pos.rend(); it++) {
        ans.push_front(x % *it);
        x /= *it;
    }
    for (int i = 0; i < n;) {
        if (s[i] == '*') {
            int j = i;
            while (j < n && s[j] == '*') {
                j++;
            }
            cout << string(ans.front(), 'b');
            ans.pop_front();
            i = j;
        } else {
            cout << 'a';
            i++;
        }
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