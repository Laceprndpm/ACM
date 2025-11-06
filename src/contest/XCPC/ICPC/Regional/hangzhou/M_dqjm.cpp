#include <bits/stdc++.h>
using namespace std;

// #define endl '\n'
#define ll long long

ll gcd(ll a, ll b)
{
    return !b ? a : gcd(b, a % b);
}

// 线段树区间修改懒标记下传

const int N = 1e6 + 7;

int a[N];

struct {
    int l, r;
    int v;
    int tag;
} tr[4 * N];

void pushup(int u)
{
    tr[u].v = gcd(tr[2 * u].v, tr[2 * u + 1].v);
}

void build(int u, int l, int r)
{
    tr[u].l = l, tr[u].r = r;
    tr[u].tag = 0;
    if (l == r) {
        tr[u].v = a[tr[u].l];
    } else {
        int mid = (l + r) >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        pushup(u);
    }
}

int result(int u, int l, int r)
{
    int ans = 0;
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].v;
    } else {
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (mid >= l) {
            ans = gcd(ans, result(2 * u, l, r));
        }
        if (mid + 1 <= r) {
            ans = gcd(ans, result(2 * u + 1, l, r));
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("20.in","r",stdin);
    // freopen("20.out","w",stdout);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        arr[0] = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = abs(arr[i] - arr[i - 1]);
        }
        build(1, 1, n);
        vector<int> l(n + 1), r(n + 1);
        for (int i = 1; i <= n; i++) {
            l[i] = i;
            r[i] = i;
        }
        stack<int> s;
        s.push(1);
        for (int i = 2; i <= n; i++) {
            while (!s.empty()) {
                int z = s.top();
                if (arr[z] > arr[i]) {
                    s.pop();
                    r[z] = i - 1;
                } else {
                    break;
                }
            }
            s.push(i);
        }
        while (!s.empty()) {
            int z = s.top();
            s.pop();
            r[z] = n;
        }
        s.push(n);
        for (int i = n - 1; i >= 1; i--) {
            while (!s.empty()) {
                int z = s.top();
                if (arr[z] >= arr[i]) {
                    s.pop();
                    l[z] = i + 1;
                } else {
                    break;
                }
            }
            s.push(i);
        }
        while (!s.empty()) {
            int z = s.top();
            s.pop();
            l[z] = 1;
        }
        map<int, int> da;
        int           shu = 0;
        for (int i = 1; i <= n; i++) {
            if (r[i] >= l[i] + 1) {
                int w = result(1, l[i] + 1, r[i]);
                if (w != 0)
                    shu++;
                else
                    continue;
                if (shu >= 2) {
                    vector<int> brr;
                    for (auto &[x, y] : da) {
                        if (w % (arr[i] + x) != 0) {
                            brr.push_back(x);
                        }
                    }
                    for (auto x : brr) {
                        da.erase(x);
                    }
                } else {
                    for (int j = 1; j * j <= w; j++) {
                        if (w % j == 0) {
                            int z1 = j, z2 = w / j;
                            if (z1 > arr[i]) {
                                da[z1 - arr[i]]++;
                            }
                            if (j * j != w) {
                                if (z2 > arr[i]) {
                                    da[z2 - arr[i]]++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (shu == 0) {
            cout << k << ' ' << (1ll + k) * k / 2 << endl;
            continue;
        }
        int ans1 = 0;
        ll  ans2 = 0;
        for (auto &[x, y] : da) {
            if (x <= k) {
                ans1++;
                ans2 += x;
            }
        }
        cout << ans1 << ' ' << ans2 << endl;
    }
    return 0;
}