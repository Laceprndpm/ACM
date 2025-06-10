#include <bits/stdc++.h>

#include <vector>
using namespace std;

const int         maxn = 2e6 + 5;
typedef long long ll;

int a[maxn];
// int pre[maxn], suf[maxn];
// pre[i]: 找到i个元素需要前几个数字
// suf[i]: 同理 后缀
set<int> s;
int      now = 0;

void solve()
{
    int n;
    cin >> n;
    vector<int> pre(n + 1), suf(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        suf[i] = pre[i] = 0;

    // 每次可以erase一个<=自己的元素
    // 找到upper
    // 如果是begin continue
    // 否则 ans++, s.erase(--pos);
    s.clear();
    for (int i = 1; i <= n; i++)
        s.insert(i);
    now = 0;
    for (int i = 1; i <= n; i++) {
        auto it = s.upper_bound(a[i]);
        if (it == s.begin()) continue;
        now++;
        pre[now] = i;
        s.erase(--it);
    }

    now = 0;
    for (int i = 1; i <= n; i++)
        s.insert(i);
    for (int i = n; i >= 1; i--) {
        auto it = s.upper_bound(a[i]);
        if (it == s.begin()) continue;
        now++;
        suf[now] = i;
        s.erase(--it);
    }
    // 枚举选几个数字
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        if (pre[i] >= suf[i]) break;
        ans += suf[i] - pre[i];
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
}