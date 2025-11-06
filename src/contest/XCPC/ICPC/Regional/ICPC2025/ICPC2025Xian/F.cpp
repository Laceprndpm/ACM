#include <bits/stdc++.h>

#include <cassert>
#include <cmath>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()

int main()
{
    int n;
    cin >> n;
    vector<int>         target(n + 1);
    vector<vector<int>> astarget(n + 1);
    vector<i64>         ti(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> target[i];
        astarget[target[i]].push_back(i);
    }
    vector<i64> ai(n + 1);
    vector<i64> finalai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
        ai[i] *= 2;
    }
    vector<i64> direct(n + 1);
    auto        get_t = [&](i64 u, i64 v) -> i64 {
        i64 posu  = ai[u];
        i64 posv  = (ti[v] == -1 ? ai[v] : finalai[v]);
        int speed = 1;
        if (ti[v] == -1) {
            if (direct[v] * direct[u] < 0) {
                speed++;
            } else {
                speed--;
            }
        }
        if (speed == 0) {
            return 4e9;
        }
        i64 res = abs(posv - posu) / speed;
        assert(res >= 0);
        return res;
    };
    for (int i = 1; i <= n; i++) {
        int v     = target[i];
        direct[i] = (ai[v] - ai[i] < 0) ? -1 : 1;
    }
    priority_queue<tuple<i64, i64, i64, int, int>, vector<tuple<i64, i64, i64, int, int>>, greater<>> action;
    for (int i = 1; i <= n; i++) {
        int v = target[i];
        i64 t = get_t(i, v);
        action.push({t, i, v, 1, 1});
    }
    while (!action.empty()) {
        auto [t, u, v, us, vs] = action.top();
        action.pop();
        if (ti[u] != -1) {
            continue;
        }
        if (vs == 1 && ti[v] != -1) {
            continue;
        }
        if (ti[u] != -1) continue;
        ti[u]      = t;
        finalai[u] = t * direct[u] + ai[u];
        for (int uu : astarget[u]) {
            if (ti[uu] != -1) continue;
            i64 newt = get_t(uu, u);
            action.push({newt, uu, u, 1, 0});
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ti[i] << ' ';
    }
}