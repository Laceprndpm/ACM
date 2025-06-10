#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
using i64            = long long;
constexpr int offset = (int)1e6 + 5;

int main()
{
    int n;
    cin >> n;
    vector<int> y0;
    vector<int> y1;
    vector<int> y2;
    // map<int, set<int>> two_one;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (y == 0) {
            y0.emplace_back(x);
        }
        if (y == 1) {
            y1.emplace_back(x);
        }
        if (y == 2) {
            y2.emplace_back(x);
        }
    }
    vector<bool> arr1(2 * offset);
    for (int i = 0; i < y0.size(); i++) {
        arr1[y0[i]] = true;
    }
    vector<array<int, 3>> ans;
    for (int j = 0; j < y1.size(); j++) {
        for (int k = 0; k < y2.size(); k++) {
            int delta = (y2[k] - y1[j]);
            if (y1[j] - delta > 0 && arr1[y1[j] - delta]) {
                ans.push_back(array<int, 3>{y1[j] - delta, y1[j], y2[k]});
            }
        }
    }
    if (ans.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    auto cmp = [&](array<int, 3> a, array<int, 3> b) -> bool {
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    };
    sort(ans.begin(), ans.end(), cmp);
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < 3; j++) {
            printf("[%d, %d]", ans[i][j], j);
            cout << " \n"[j == 2];
        }
    }
    return 0;
}