#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           k, n;

void query(int idx)
{
    cout << "? " << idx + 1 << endl;
}

void No()
{
    cout << "! -1" << endl;
}

void conf(int l1)
{
    cout << "! " << l1 + 1 << ' ' << n - l1 - 1 << '\n';
}

void solve()
{
    cin >> n >> k;
    vector<i64> arrI(k);
    for (int i = 0; i < k; i++) {
        query(i);
        cin >> arrI[i];
    }
    vector<i64> brrI(k);
    for (int i = 0; i < k; i++) {
        query(i + n - k);
        int idx = (i + n - k) % k;
        cin >> brrI[idx];
    }
    int first_different_idx = -1;
    for (int i = 0; i < k; i++) {
        if (arrI[i] != brrI[i]) {
            first_different_idx = i;
            break;
        }
    }
    if (first_different_idx == -1) {
        if (n == 2 * k) {
            conf(k - 1);
            return;
        }
        No();
        return;
    }
    int blocks = n / k;
    if (first_different_idx < n - blocks * k) {
        blocks++;
    }
    int l = 0, r = blocks;
    int ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        query(mid * k + first_different_idx);
        int cur;
        cin >> cur;
        if (cur == arrI[first_different_idx]) {
            ans = mid;
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    int firstpre = ans * k + first_different_idx;
    int lastidx  = ans * k + first_different_idx + k;
    firstpre     = max(firstpre, k - 1);
    lastidx      = min(lastidx, n - k);
    for (int i = 1; i < k; i++) {
        int idx  = i + ans * k + first_different_idx;
        int idx2 = i + first_different_idx;
        idx2 %= k;
        query(idx);
        i64 temp;
        cin >> temp;
        if (temp == arrI[idx2] && temp != brrI[idx2]) {
            firstpre = max(idx, firstpre);
        }
        if (temp == brrI[idx2] && temp != arrI[idx2]) {
            lastidx = min(idx, lastidx);
        }
    }
    if (lastidx != firstpre + 1) {
        No();
    } else {
        conf(firstpre);
    }
}

signed main(int argc, char** argv)
{
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