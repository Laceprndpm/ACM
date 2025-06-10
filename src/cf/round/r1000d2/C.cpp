#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
        degree[u]++;
        degree[v]++;
    }
    int maxdegreeIdx = max_element(degree.begin() + 1, degree.end()) - degree.begin();
    int maxdegree    = degree[maxdegreeIdx];
    if (count(degree.begin() + 1, degree.end(), maxdegree) > 2) {
        cout << maxdegree * 2 - 1 << endl;
        return;
    } else if (count(degree.begin() + 1, degree.end(), maxdegree) == 2) {
        for (int i : graph[maxdegreeIdx]) {
            if (degree[i] == maxdegree) {
                cout << maxdegree * 2 - 2 << endl;
                return;
            }
        }
        cout << maxdegree * 2 - 1 << endl;
        return;
    } else {
        int secondMaxDegree = 0;
        int cnt             = 0;
        for (int i = 1; i <= n; i++) {
            if (degree[i] < maxdegree && degree[i] > secondMaxDegree) {
                secondMaxDegree = degree[i];
                cnt             = 1;
            } else if (degree[i] == secondMaxDegree) {
                cnt++;
            }
        }
        int newcnt = 0;
        for (int adj : graph[maxdegreeIdx]) {
            if (degree[adj] == secondMaxDegree) {
                newcnt++;
            }
        }
        if (newcnt == cnt) {
            cout << maxdegree + secondMaxDegree - 2 << endl;
            return;
        } else {
            cout << maxdegree + secondMaxDegree - 1 << endl;
            return;
        }
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}