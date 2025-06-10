#include <cmath>
#include <queue>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int getRoot(int x)
{
    return log10(x) + 1;
}

void solve()
{
    int n;
    cin >> n;
    priority_queue<int> pqA;
    priority_queue<int> pqB;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        pqA.emplace(a);
    }
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        pqB.emplace(b);
    }
    int cnt = 0;
    while (!pqA.empty()) {
        if (pqA.top() == pqB.top()) {
            pqA.pop();
            pqB.pop();
        } else if (pqA.top() > pqB.top()) {
            int cur = pqA.top();
            pqA.pop();
            pqA.emplace(getRoot(cur));
            cnt++;
        } else {
            int cur = pqB.top();
            pqB.pop();
            pqB.emplace(getRoot(cur));
            cnt++;
        }
    }
    cout << cnt << '\n';
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