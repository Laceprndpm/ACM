#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define pb push_back
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define int long long
template <typename T>
struct Fenwick
{
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v)
    {
        for (int i = x + 1; i <= n; i += i & -i)
        {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i)
        {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }

    int select(const T &k)
    {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2)
        {
            if (x + i <= n && cur + a[x + i - 1] <= k)
            {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> prefix(n + 1);
    vector<int> arr(n + 1);
    vector<int> ans(n + 1);
    Fenwick<int> fk(n + 1);
    vector<int> vis(n + 1);
    prefix[1] = 1;
    i64 curans = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    vis[arr[1]]++;
    fk.add(arr[1], 1);
    for (int i = 2; i <= n; i++)
    {
        if (arr[prefix[i - 1]] < arr[i])
        {
            for (int j = i - 1; j >= prefix[i - 1]; j--)
            {
                if (--vis[arr[j]] == 0)
                {
                    fk.add(arr[j], -1);
                }
            }
            vis[arr[i]]++;
            fk.add(arr[i], 1);
            curans = ans[prefix[i - 1]] + 1;
            for (int j = prefix[i - 1] + 1; j <= i - 1; j++)
            {
                curans += fk.rangeSum(arr[j] + 1, n + 1);
                if (vis[arr[j]]++ == 0)
                {
                    fk.add(arr[j], 1);
                }
            }
            curans += fk.rangeSum(arr[prefix[i - 1]] + 1, n + 1);
            if (vis[arr[prefix[i - 1]]]++ == 0)
            {
                fk.add(arr[prefix[i - 1]], 1);
            }
            ans[i] = curans;
            prefix[i] = i;
        }
        else
        {
            curans += fk.rangeSum(arr[i] + 1, n + 1);
            ans[i] = curans;
            if (vis[arr[i]]++ == 0)
            {
                fk.add(arr[i], 1);
            }
            prefix[i] = prefix[i - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " \n"[i == n];
    }
}

signed main()
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