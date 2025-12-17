#include <bits/stdc++.h>

#include <cassert>
using namespace std;
using ll = long long;
ll   a[25], s[1 << 20];
int  d[1 << 20];
bool v[1 << 20];

struct O {
    int x, y;
    ll  z;
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    ll t = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t += a[i];
    }
    if (t % n) {
        cout << -1;
        return 0;
    }
    t /= n;
    for (int i = 0; i < (1 << n); i++) {
        ll  c = 0;
        int k = 0;
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1) {
                c += a[j];
                k++;
            }
        if (k > 0 && c == t * k) v[i] = true;
    }
    for (int i = 1; i < (1 << n); i++) {
        int m = 0;
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1) m = max(m, d[i ^ (1 << j)]);
        d[i] = m + (v[i] ? 1 : 0);
    }
    vector<int> p;
    int         c = (1 << n) - 1;
    while (c > 0) {
        if (v[c]) p.push_back(c);
        int g = d[c] - (v[c] ? 1 : 0);
        for (int j = 0; j < n; j++) {
            if (((c >> j) & 1) && d[c ^ (1 << j)] == g) {
                c ^= (1 << j);
                break;
            }
        }
    }
    assert(n - d[(1 << n) - 1] <= n);
    cout << n - d[(1 << n) - 1] << "\n";
    vector<O> q;
    int       l = 0;
    for (int i = p.size() - 1; i >= 0; i--) {
        int m = p[i] ^ l;
        l     = p[i];
        vector<int> g, r;
        for (int j = 0; j < n; j++) {
            if ((m >> j) & 1) {
                if (a[j] > t)
                    g.push_back(j);
                else if (a[j] < t)
                    r.push_back(j);
            }
        }
        while (!g.empty() && !r.empty()) {
            int gi = g.back(), ri = r.back();
            ll  amt = min(a[gi] - t, t - a[ri]);
            q.push_back({gi + 1, ri + 1, amt});
            a[gi] -= amt;
            a[ri] += amt;
            if (a[gi] == t) g.pop_back();
            if (a[ri] == t) r.pop_back();
        }
    }
    for (auto& x : q) cout << x.x << " " << x.y << " " << x.z << "\n";
    return 0;
}