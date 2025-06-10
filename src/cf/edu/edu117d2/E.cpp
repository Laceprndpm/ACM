#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n;
    cin >> n;
    vector<int>            arrM((int)2e5 + 50);
    vector<pair<int, int>> input(n);
    for (int i = 0; i < n; i++) {
        cin >> input[i].first >> input[i].second;
    }
    i64         curE = 0, curD = 1;
    vector<int> idx((int)2e5 + 50);
    iota(idx.begin(), idx.end(), 0);
    vector<int> ansVec;
    for (int j = 1; j < min<i64>(20, n + 1); j++) {
        i64 E = 0;
        arrM.assign(arrM.size(), 0);
        for (int i = 0; i < n; i++) {
            int mi = input[i].first, ki = input[i].second;
            ki = min(ki, j);
            arrM[mi] += ki;
        }
        sort(idx.begin(), idx.end(), [&](int u, int v) {
            return arrM[u] > arrM[v];
        });
        for (int i = 0; i < j; i++) {
            E += arrM[idx[i]];
        }
        if (curE * j < E * curD) {
            curE = E, curD = j;
            ansVec.clear();
            for (int i = 0; i < j; i++) {
                ansVec.push_back(idx[i]);
            }
        }
    }
    arrM.assign(arrM.size(), 0);

    for (int i = 0; i < n; i++) {
        int mi = input[i].first, ki = input[i].second;
        arrM[mi] += ki;
    }

    sort(idx.begin(), idx.end(), [&](int u, int v) {
        return arrM[u] > arrM[v];
    });
    vector<i64> prefix((int)2e5 + 51);
    for (int i = 0; i < (int)2e5 + 50; i++) {
        prefix[i + 1] = prefix[i] + arrM[idx[i]];
    }
    for (i64 i = 20; i <= n; i++) {
        if (curE * i < prefix[i] * curD) {
            curE = prefix[i], curD = i;
        }
    }

    if (curD < 20) {
        cout << curD << '\n';
        for (int i : ansVec) {
            assert(i);
            cout << i << ' ';
        }
    } else {
        cout << curD << '\n';
        for (int i = 0; i < curD; i++) {
            assert(idx[i]);
            cout << idx[i] << ' ';
        }
    }
    return 0;
}