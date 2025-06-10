#include <algorithm>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
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
    i64 n, q;
    cin >> n >> q;

    vector<i64> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    vector<i64> hash1_map(n + 1), hash2_map(n + 1);
    mt19937     rd;
    rd.seed(time(0));
    iota(hash1_map.begin(), hash1_map.end(), 0);
    iota(hash2_map.begin(), hash2_map.end(), n);
    shuffle(hash1_map.begin(), hash1_map.end(), rd);
    shuffle(hash2_map.begin(), hash2_map.end(), rd);
    vector<i64> hash1a(n), hash2a(n), hash1b(n), hash2b(n);
    for (int i = 0; i < n; i++) {
        hash1a[i] = hash1_map[arr[i]];
        hash2a[i] = hash2_map[arr[i]];
        hash1b[i] = hash1_map[brr[i]];
        hash2b[i] = hash2_map[brr[i]];
    }
    vector<i64> prefixHash1(n + 1, 0), prefixHash2(n + 1, 0);
    vector<i64> prefixHash1b(n + 1, 0), prefixHash2b(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixHash1[i + 1]  = prefixHash1[i] + hash1a[i];
        prefixHash2[i + 1]  = prefixHash2[i] + hash2a[i];
        prefixHash1b[i + 1] = prefixHash1b[i] + hash1b[i];
        prefixHash2b[i + 1] = prefixHash2b[i] + hash2b[i];
    }
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        i64 h1a = prefixHash1[r1] - prefixHash1[l1 - 1];
        i64 h2a = prefixHash2[r1] - prefixHash2[l1 - 1];
        i64 h1b = prefixHash1b[r2] - prefixHash1b[l2 - 1];
        i64 h2b = prefixHash2b[r2] - prefixHash2b[l2 - 1];
        if (h1a == h1b && h2a == h2b)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}