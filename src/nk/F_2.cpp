#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void Tokisaki()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<int, bool> mp;
    int            size_cnt = 0, pla_cnt = 0;
    vector<int>    a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (mp[a[i]] == 0) size_cnt++;
        mp[a[i]] = 1;
    }
    vector<int> pla;
    int         res = 0;
    for (auto i : s) {
        if (i == '(') {
            res++;
            pla.push_back(res);
            if (res == 1) pla_cnt++;
        } else
            res--;
    }
    if (size_cnt < pla_cnt) {
        cout << "NO\n";
        return;
    } else
        cout << "YES\n";
    sort(a.begin(), a.end());
    map<int, bool> vis, id;
    vector<int>    ans(n);
    for (int i = 0, j = 0; i < n && j < n;) {
        if (vis[a[i]] && i < n) i++;
        if (i >= n) break;
        if (pla[j] != 1 && j < n) j++;
        if (j >= n) break;
        ans[j]    = a[i];
        id[i]     = 1;
        vis[a[i]] = 1;
    }
    for (int i = 0, j = 0; i < n && j < n;) {
        if (ans[j] && j < n) j++;
        if (j >= n) break;
        if (id[i] && i < n) i++;
        if (i >= n) break;
        ans[j] = a[i];
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin>>_;
    while (_--)
        Tokisaki();
    return 0;
}