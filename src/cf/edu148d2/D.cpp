#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
vector<int>   arr;
int           n, k;

void solve()
{
    int q;
    cin >> q;
    int cntq = q;

    vector<int> brr(arr);
    if (q <= n) {
        for (int i = q; i >= 1; i--) {
            brr[q - i] += i;
        }
        cout << *min_element(brr.begin(), brr.end()) << ' ';
        return;
    } else {
        if ((n - q) % 2 == 0) {
            for (int i = 0; i < n; i++) {
                brr[i] += cntq;
                cntq--;
            }
            q -= n;
        } else {
            for (int i = 0; i < n - 1; i++) {
                brr[i] += cntq;
                cntq--;
            }
            q -= n - 1;
        }
    }

    priority_queue<int> pq;
    for (int i : brr) {
        pq.push(i);
    }

    for (int i = q; i >= 1; i--) {
        int cur = pq.top();
        pq.pop();
        cur--;
        i--;
        pq.push(cur);
    }
    int last = pq.top();
    pq.pop();
    while (!pq.empty()) {
        last = pq.top();
        pq.pop();
    }
    cout << last << ' ';
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
    cin >> n >> k;
    arr.resize(n);
    for (int& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    while (k--) {
        solve();
    }
    return 0;
}