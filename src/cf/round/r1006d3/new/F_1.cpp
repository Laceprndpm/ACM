#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 1e6;

vector<int> cnt2(MAXN + 1);
vector<int> prefix(MAXN + 1);

void init()
{
    for (int i = 1; i <= MAXN; i++) {
        if (i % 2 == 0) {
            cnt2[i] = cnt2[i / 2] + 1;
        } else {
            cnt2[i] = 0;
        }
    }
    for (int i = 1; i <= MAXN; i++) {
        prefix[i] = prefix[i - 1] + cnt2[i];
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    n--;
    for (int i = 0; i <= n; i++) {
        if (prefix[n] - prefix[n - i] - prefix[i]) {
            cout << 0 << ' ';
        } else {
            cout << k << ' ';
        }
    }
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
