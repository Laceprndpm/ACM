#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
using i64                  = long long;
using u64                  = unsigned long long;
using PII                  = pair<int, int>;
constexpr int          INF = 1e9;
array<int, 11>         global_sta;
array<vector<int>, 10> global_arr;
array<int, 10>         idx;
i64                    ans = 0;
vector<int>            ansvec;
int                    n;

struct Hash_c {
    Hash_c(){};
    i64      MOD1 = 1e9 + 7, base = 114514;
    set<u64> hash1;
    set<i64> hash2;

    u64 hashArray(const std::vector<int>& arr)
    {
        return std::accumulate(arr.begin(), arr.end(), 0ULL, [](u64 seed, int val) {
            return seed ^ (std::hash<int>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
        });
    }

    i64 hashArray2(const vector<int>& arr)
    {
        i64 res = 0;
        for (int i : arr) {
            res *= base;
            res %= MOD1;
            res += i;
            res %= MOD1;
        }
        return res;
    }

    void add(const vector<int>& t)
    {
        u64 val_hash1 = hashArray(t);
        i64 val_hash2 = hashArray2(t);
        hash1.insert(val_hash1);
        hash2.insert(val_hash2);
    }

    int query(auto& t)
    {
        u64 val_hash1 = hashArray(t);
        i64 val_hash2 = hashArray2(t);
        return hash1.count(val_hash1) && hash2.count(val_hash2);
    }
} h;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> n;
    vector<int> carr(n);
    for (int i = 0; i < n; i++) {
        int ci;
        cin >> ci;
        carr[i] = ci - 1;
        vector<int> arr(ci);
        global_sta[i] = ci - 1;
        for (int i = 0; i < ci; i++) {
            cin >> arr[i];
        }
        global_arr[i] = std::move(arr);
    }
    int m;
    cin >> m;
    vector<vector<int>> mbrr(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        vector<int> pt(n);
        for (int j = 0; j < n; j++) {
            cin >> pt[j];
            pt[j]--;
            mbrr[i][j] = pt[j];
        }
        h.add(pt);
    }
    i64 ans = 0;
    if (!h.query(carr)) {
        ansvec = carr;
    } else {
        for (int k = 0; k < m; k++) {
            for (int j = 0; j < n; j++) {
                if (mbrr[k][j] == 0) continue;
                mbrr[k][j]--;
                if (!h.query(mbrr[k])) {
                    i64 res = 0;
                    for (int p = 0; p < n; p++) {
                        res += global_arr[p][mbrr[k][p]];
                    }
                    if (res > ans) {
                        ans    = res;
                        ansvec = mbrr[k];
                    }
                }
                mbrr[k][j]++;
            }
        }
    }
    if (!ansvec.empty())
        for (int i = 0; i < n; i++) {
            cout << ansvec[i] + 1 << ' ';
        }
    else {
        for (int i = 0; i < n; i++) {
            cout << carr[i] + 1 << ' ';
        }
    }
    return 0;
}