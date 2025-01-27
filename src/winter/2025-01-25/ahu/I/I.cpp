#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int>            degree(n + 1, 0);
    vector<pair<int, int>> Graph(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
        Graph[i] = {a, b};
    }
    int has3degree = -1;
    for (int i = 1; i <= n; i++) {
        if (degree[i] >= 3) {
            has3degree = i;
            break;
        }
    }
    int idx_0 = 0;
    int idx   = 3;
    if (has3degree != -1)
        for (int i = 1; i <= n - 1; i++) {
            if (idx_0 <= 2 && (Graph[i].first == has3degree || Graph[i].second == has3degree)) {
                cout << idx_0++ << '\n';
            } else {
                cout << idx++ << '\n';
            }
        }
    else {
        for (int i = 0; i < n - 1; i++)
            cout << i << '\n';
    }
    return 0;
}