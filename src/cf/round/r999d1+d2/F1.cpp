#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void myreve(auto it1, auto it2, int num)
{
    int cnt = 0;
    while (cnt < num && it1 != it2 && (it1 != --it2)) {
        iter_swap(it1, it2);
        ++it1;
        cnt++;
    }
}

void solve()
{
    string a, b;
    cin >> a >> b;
    int         n   = a.length();
    int         ans = 0;
    vector<int> tail(n + 1);
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && a[j] == a[i]) {
            j++;
        }
        tail[i] = j;
        i       = j;
    }
    tail[n] = n;
    for (int i = 0; i < n;) {
        if (a[i] != b[i]) {
            if (i != 0 && a[i] == a[i - 1]) break;
            int head2 = tail[i];
            ans++;
            if (head2 < n && a[head2] != a[i]) {
                int tail2 = tail[head2];
                myreve(a.begin() + i, a.begin() + tail2, min(tail2 - head2, head2 - i));
                tail[i]                   = i + (tail2 - head2);
                tail[i + (tail2 - head2)] = tail[tail2];
                tail[tail2]               = 0;
            } else {
                break;
            }
        }
        i = tail[i];
    }
    if (a == b) {
        cout << ans << '\n';
    } else {
        cout << -1 << '\n';
    }
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