#ifdef V0
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a_arr(n + 1);
    vector<int> b_arr(n + 1);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        a_arr[i] = a;
        b_arr[i] = b;
    }
    set<int> uniqueSet;
    uniqueSet.insert(a_arr.begin() + 1, a_arr.end());
    uniqueSet.insert(b_arr.begin() + 1, b_arr.end());
    vector<int> r2v(uniqueSet.size() + 1);
    {
        int idx = 1;
        for (int iter : uniqueSet) {
            r2v[idx] = iter;
            idx++;
        }
    }
    map<int, int> v2r;
    for (int i = 1; i <= uniqueSet.size(); i++) {
        v2r[r2v[i]] = i;
    }
    vector<bool> isFire(uniqueSet.size() + 1, false);
    for (int i = 1; i <= n; i++) {
        for (int j = v2r[a_arr[i]]; j < v2r[b_arr[i]]; j++) {
            isFire[j] = true;
        }
    }
    LL ans = 0;
    for (int i = 1; i < v2r.size(); i++) {
        if (isFire[i]) {
            ans += r2v[i + 1] - r2v[i];
        }
    }
    cout << ans;
    return 0;
}
#endif

#ifdef V1
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a_arr(n + 1);
    vector<int> b_arr(n + 1);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        a_arr[i] = a;
        b_arr[i] = b;
    }
    set<int> uniqueSet;
    uniqueSet.insert(a_arr.begin() + 1, a_arr.end());
    uniqueSet.insert(b_arr.begin() + 1, b_arr.end());
    vector<int> r2v(uniqueSet.size() + 1);
    {
        int idx = 1;
        for (int iter : uniqueSet) {
            r2v[idx] = iter;
            idx++;
        }
    }
    map<int, int> v2r;
    for (int i = 1; i <= uniqueSet.size(); i++) {
        v2r[r2v[i]] = i;
    }
    vector<int> isFire(uniqueSet.size() + 1, 0);
    for (int i = 1; i <= n; i++) {
        // for (int j = v2r[a_arr[i]]; j < v2r[b_arr[i]]; j++) {
        //     isFire[j] = true;
        // }
        isFire[v2r[a_arr[i]]]++;
        isFire[v2r[b_arr[i]]]--;
    }
    LL  ans = 0;
    int cur = 0;
    for (int i = 1; i < v2r.size(); i++) {
        cur += isFire[i];
        if (cur != 0) {
            ans += r2v[i + 1] - r2v[i];
        }
    }
    cout << ans;
    return 0;
}
#endif

#include <bits/stdc++.h>
using namespace std;
#define MAXN 20010
int       n, a[MAXN], b[MAXN], f[MAXN * 2], dtop, ctop, d[MAXN * 2];
long long c[MAXN * 2];
long long ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        d[++dtop] = a[i];
        d[++dtop] = b[i];
    }
    sort(d + 1, d + dtop + 1);
    for (int i = 1; i <= dtop; i++) {
        if (d[i] != d[i - 1] || i == 1)
            c[++ctop] = d[i];
    }
    for (int i = 1; i <= n; ++i) {
        int x = lower_bound(c + 1, c + ctop + 1, a[i]) - c;
        int y = lower_bound(c + 1, c + ctop + 1, b[i]) - c;
        for (int j = x; j < y; j++) {
            f[j] = 1;
        }
    }
    for (int i = 1; i < ctop; i++) {
        if (f[i])
            ans += c[i + 1] - c[i];
    }
    printf("%lld\n", ans);
    return 0;
}