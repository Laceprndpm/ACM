#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define fi first
#define se second
#define pb push_back
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define bk back()
int n, m, k, w;
vector<int> ansvec;
int calc(int r1, int l2)
{
    return max(r1 - l2 + 1, 0);
}
pair<int, int> mov(pair<int, int> a, int k)
{
    return {a.fi - k, a.se - k};
}
int check(vector<int> red, int l, int r)
{
    if (red.empty())
        return 0;
    int n = red.size();
    int last = 0;
    vector<pair<int, int>> square;
    for (int i = 0; i < n; i++)
    {
        if (last >= red[i])
            continue;
        last = red[i] + k - 1;
        square.pb({red[i], red[i] + k - 1});
    }
    vector<pair<int, int>> shiftedsquare;
    int cross = calc(square.bk.se, r);
    if (cross == 0)
    {
        for (auto [l, r] : square)
        {
            ansvec.pb(l);
        }
        return square.size();
    }
    else
    {
        shiftedsquare.pb(mov(square.bk, cross));
        square.pop_back();
    }
    while (!square.empty())
    {
        int k = calc(square.bk.se, shiftedsquare.bk.fi);
        shiftedsquare.pb(mov(square.bk, k));
        square.pop_back();
    }
    if (shiftedsquare.bk.fi > l)
    {
        for (auto [l, r] : shiftedsquare)
        {
            ansvec.pb(l);
        }
        return shiftedsquare.size();
    }
    else
    {
        return -1;
    }
}
void solve()
{
    ansvec.clear();
    cin >> n >> m >> k >> w;
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        arr.pb({p, 0});
    }
    for (int i = 0; i < m; i++)
    {
        int p;
        cin >> p;
        arr.pb({p, 1});
    }
    arr.pb({w + 1, 1});
    int last = 0;
    sort(all(arr));
    vector<int> reds;
    i64 ans = 0;
    for (int i = 0; i < n + m + 1; i++)
    {
        if (arr[i].se == 1)
        {
            int res = check(reds, last, arr[i].fi);
            if (res == -1)
            {
                cout << -1 << '\n';
                return;
            }
            ans += res;
            last = arr[i].fi;
            reds.clear();
        }
        else
        {
            reds.pb(arr[i].fi);
        }
    }
    cout << ans << '\n';
    for (int i : ansvec)
    {
        cout << i << ' ';
    }
    cout << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}