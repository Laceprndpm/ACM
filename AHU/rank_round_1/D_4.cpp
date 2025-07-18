#include <bits/stdc++.h>

#include <random>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
#define endl '\n'
using pll   = pair<ll, ll>;
using pii   = pair<int, int>;
const int N = 1e5 + 10;
mt19937   rnd(114514);

// #define int ll
struct node {
    int v[11][4];
    int len;
} f[11][400];

int mp[200], a[N];
int st[N], ed[N], bel[N];

void UraykevoliQwQ()
{
    mp['A'] = 0;
    mp['T'] = 1;
    mp['G'] = 2;
    mp['C'] = 3;
    string s;
    cin >> s;
    int n = s.size();
    s     = " " + s;
    for (int i = 1; i <= n; i++)
        a[i] = mp[s[i]];
    int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        st[i] = n / sq * (i - 1) + 1;
        ed[i] = n / sq * i;
    }
    ed[sq] = n;
    for (int i = 1; i <= sq; i++) {
        for (int j = st[i]; j <= ed[i]; j++)
            bel[j] = i;
        for (int l = 1; l <= 10; l++) {
            f[l][i].len = ed[i] - st[i] + 1;
            for (int j = 0; j < f[l][i].len; j++) {
                f[l][i].v[j % l][a[st[i] + j]]++;
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int  pos;
            char x;
            cin >> pos >> x;
            int val = mp[x];
            for (int l = 1; l <= 10; l++) {
                f[l][bel[pos]].v[(pos - st[bel[pos]]) % l][a[pos]]--;
                f[l][bel[pos]].v[(pos - st[bel[pos]]) % l][val]++;
            }
            a[pos] = val;
        } else {
            int    l, r;
            string e;
            cin >> l >> r >> e;
            int len = e.size();
            int ans = 0;
            if (bel[l] == bel[r]) {
                for (int i = l; i <= r; i++) {
                    if (a[i] == mp[e[(i - l) % len]]) ans++;
                }
                cout << ans << endl;
                continue;
            } else {
                int ans = 0;
                for (int i = l; i <= ed[bel[l]]; i++) {
                    if (a[i] == mp[e[(i - l) % len]]) ans++;
                }
                for (int i = st[bel[r]]; i <= r; i++) {
                    if (a[i] == mp[e[(i - l) % len]]) ans++;
                }
                int now = ed[bel[l]] - l + 1;
                for (int i = bel[l] + 1; i < bel[r]; i++) {
                    for (int j = 0; j < e.size(); j++) {
                        ans += f[len][i].v[((j - now) % len + len) % len][mp[e[j]]];
                    }
                    now += f[len][i].len;
                }
                cout << ans << endl;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _ = 1;
    // cin >>_;
    while (_--)
        UraykevoliQwQ();
    // return 0;
}