#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

int                    n, q;
vector<array<int, 30>> highIdx(4e5 + 4);
// arr[i][j]为(0, i]内最靠右的最高位大于j位的数的索引
vector<int> prefix(4e5 + 4);
vector<int> weight(4e5 + 4);

int getHighbit(int x)
{
    int cnt = -1;
    while (x > 0) {
        cnt++;
        x >>= 1;
    }
    return cnt;
}

void initPrefixAndHighIdx(int l, int r)
{
    for (int i = l; i <= r; i++) {
        prefix[i] = prefix[i - 1] ^ weight[i];
    }
    for (int d = 29; d >= 0; d--) {
        for (int i = l; i <= r; i++) {
            bool cur = (weight[i] >> d) > 0;
            if (cur) {
                highIdx[i][d] = i;
            } else {
                highIdx[i][d] = highIdx[i - 1][d];
            }
        }
    }
}

int eat(int x)
{
    int high = getHighbit(x);
    if (high == -1) {
        return 0;
    }
    int nxt = highIdx[n][high];
    x ^= prefix[n] ^ prefix[nxt];
    int length_eat = n - nxt;
    n              = nxt;
    if (x >= weight[nxt] && n > 0) {
        x ^= weight[nxt];
        n--;
        return length_eat + 1 + eat(x);
    } else {
        return length_eat;
    }
}

void solve()
{
    cin >> n >> q;
    int N = n;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    initPrefixAndHighIdx(1, n);
    while (q--) {
        int x;
        cin >> x;
        cout << eat(x) << ' ';
        n = N;
    }
    cout << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}