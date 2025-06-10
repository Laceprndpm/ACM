// #include <cassert>
// #include <iostream>
// #include <map>
// #include <vector>
// using namespace std;
// using i64         = long long;
// using PII         = pair<int, int>;
// constexpr int INF = 1e9;

// signed main(int argc, char** argv)
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
// #ifdef BATCH
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
//     int n;
//     cin >> n;
//     vector<int> arr(n);
//     // arr.reserve(n);
//     for (int& i : arr) {
//         cin >> i;
//     }
//     map<int, int> lastmp;
//     int           ans = 0;
//     for (int i = 0; i < n; i++) {
//         if (i + 1 < n && arr[i] == arr[i + 1]) {
//             int j = i;
//             while (j + 1 < n && arr[j] == arr[j + 1]) {
//                 if (lastmp.count(arr[j]) != 0 && lastmp[arr[j]] >= i) {
//                     break;
//                 }
//                 lastmp[arr[j]] = j + 1;
//                 j += 2;
//             }
//             ans = max(ans, j - i);
//             if (j + 1 >= n) {
//                 break;
//             }
//             if (arr[j] != arr[j + 1]) {
//                 i = j - 2;
//                 continue;
//             }
//             if (lastmp.count(arr[j]) != 0 && lastmp[arr[j]] >= i) {
//                 i = lastmp[arr[j]];
//                 lastmp.clear();
//                 continue;
//             }
//             assert(0);
//         }
//         lastmp[arr[i]] = i;
//     }
//     cout << ans << '\n';
//     return 0;
// }
#include <cassert>
#include <iostream>
#include <map>
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
    int n;
    cin >> n;
    vector<int> arr(n);
    // arr.reserve(n);
    for (int& i : arr) {
        cin >> i;
    }
    map<int, int> lastmp;
    int           ans = 0;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && arr[i] == arr[i + 1]) {
            int j = i;
            lastmp.clear();
            while (j + 1 < n && arr[j] == arr[j + 1]) {
                if (lastmp.count(arr[j]) != 0) {
                    if (lastmp[arr[j]] > i) {
                        break;
                    }
                }
                lastmp[arr[j]] = j + 1;
                j += 2;
            }
            ans = max(ans, j - i);
            if (j + 1 >= n) {
                break;
            }
            if (arr[j] != arr[j + 1]) {
                i = j - 2;
                continue;
            }
            if (lastmp.count(arr[j]) != 0 && lastmp[arr[j]] >= i) {
                i = lastmp[arr[j]] - 1;
                continue;
            }
            assert(0);
        }
        lastmp[arr[i]] = i;
    }
    cout << ans << '\n';
    return 0;
}