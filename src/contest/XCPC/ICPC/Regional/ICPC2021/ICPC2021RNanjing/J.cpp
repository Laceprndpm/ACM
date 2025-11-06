#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define pb push_back
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;
    i64 ans = 1e9;
    map<pair<int, int>, int> mmp;
    set<pair<int, int>> vis;
    if (b < a)
        swap(a, b);
    int gap = abs(b - a);
    vector<int> factors;
    for (i64 i = 1; i * i <= gap; i++)
    {
        if (gap % i == 0)
        {
            factors.pb(i);
            if (i * i != gap)
                factors.pb(gap / i);
        }
    }
    sort(all(factors));
    vector<vector<int>> primefactors(factors.size());
    for (int i = 0; i < factors.size(); i++)
    {
        int vval = factors[i];
        i64 j;
        for (j = 2; j * j <= vval; j++)
        {
            if (vval % j == 0)
            {
                primefactors[i].pb(j);
                while (vval % j == 0)
                {
                    vval /= j;
                }
            }
        }
        if (vval != 1)
            primefactors[i].pb(vval);
    }
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.push({0, a, b - a});
    while (!pq.empty())
    {
        auto [dist, ca, gap] = pq.top();
        pq.pop();
        if (vis.count({ca, gap}))
            continue;
        ans = min(ans, ca - 1 + dist);
        vis.insert({ca, gap});
        int id = lower_bound(all(factors), gap) - factors.begin();
        for (int nxtp : primefactors[id])
        {
            if (ca % nxtp == 0)
            {
                pair<int, int> v = {ca / nxtp, gap / nxtp};
                if (mmp.count(v) == 0 || mmp[v] > dist + 1)
                {
                    mmp[v] = dist + 1;
                    pq.push({dist + 1, v.first, v.second});
                }
            }
            else
            {
                int val1 = ca / nxtp * nxtp;
                int d1 = dist + 1 + abs(val1 - ca);
                pair<int, int> v = {val1 / nxtp, gap / nxtp};
                if (mmp.count(v) == 0 || mmp[v] > d1)
                {
                    mmp[v] = d1;
                    pq.push({d1, v.first, v.second});
                }
                int val2 = ((ca - 1) / nxtp + 1) * nxtp;
                int d2 = dist + 1 + abs(val2 - ca);
                v = {val2 / nxtp, gap / nxtp};
                if (mmp.count(v) == 0 || mmp[v] > d2)
                {
                    mmp[v] = d2;
                    pq.push({d2, v.first, v.second});
                }
            }
        }
    }
    cout << ans << '\n';
}
signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}