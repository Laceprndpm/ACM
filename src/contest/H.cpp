#include <functional>
#define REMOVE_ME
#include <bits/stdc++.h>

#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second - a.first > b.second - b.first;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> mp(k);
    vector<pair<int, int>> line;
    map<int, int>          len;
    for (int i = 0; i < k; i++) {
        cin >> mp[i].first >> mp[i].second;
        line.push_back({mp[i].second - mp[i].first + 1, mp[i].first});
        len[mp[i].second - mp[i].first + 1]++;
    }
    sort(line.begin(), line.end(), greater());
    vector<int> fa(n + 1);
    for (int i = 0; i < k; i++) {
        for (int j = mp[i].first + 1; j <= mp[i].second; j++) {
            fa[j] = j - 1;
        }
    }
    if (len.rbegin()->first == 1) {
        if (n == 1) {
            cout << 0 << '\n';
            return;
        } else {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }
    if (len.rbegin()->second <= 1) {
        fa[line[0].second] = 0;
        int root           = line[0].second;
        for (int i = 1; i < k; i++) {
            fa[line[i].second] = root;
        }
    } else {
        if (line.back().first <= line[0].first - 2) {
            fa[line.back().second] = line[0].second + 1;
            int root               = line[0].second;
            for (int i = 1; i < k - 1; i++) {
                fa[line[i].second] = root;
            }
        } else {
            // cout<<"XXX"<<' ';
            cout << "IMPOSSIBLE" << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << fa[i] << ' ';
    cout << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}