#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int lowbit(int x)
{
    return x & -x;
}

void update(vector<int> &bit, int x, int v)
{
    for (int i = x; i < bit.size(); i += lowbit(i)) {
        bit[i] += v;
    }
}

int query(vector<int> &bit, int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += bit[i];
    }
    return res;
}

int n, m;

signed main()
{
    cin >> n;
    vector<int>            bit(n + 1, 0);
    vector<pair<int, int>> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i].first;
        ai[i].second = i;
    }
    vector<int> bi(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bi[i];
        update(bit, i, bi[i]);
    }
    sort(ai.begin() + 1, ai.end());
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // 当前所在位置，需要移到i处。。。
        int place = ai[i].second;
        int value = bi[place];
        update(bit, place, -value);
        ans += query(bit, place) * value;
    }
    cout << ans;
    return 0;
}