#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;
int           c   = 6;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 1 2 3 4
    // 2 3 4 1 3 + 3 = 6
    // 3 1 4 2 2 + 1 + 1 + 2 = 6
    // 3 - 4
    // 4 - 4
    // 5 - 6
    // 6 - 6 偶数只需要两两配队
    // 奇数呢，先两两，还剩三个 1 ~ 2 2 ~ 3 1 ~ 3
    // vector<int> arr1(c);
    // vector<int> arr2(c);
    // iota(all(arr1), 1), iota(all(arr2), 1);
    // vector<int> ans;
    // int         ansVal = INF;
    // do {
    //     int disok = 0;
    //     for (int i = 0; i < c; i++) {
    //         if (arr1[i] == arr2[i]) {
    //             disok = 1;
    //             break;
    //         }
    //     }
    //     if (disok) continue;
    //     i64 sum = 0;
    //     for (int i = 0; i < c; i++) {
    //         sum += abs(arr1[i] - arr2[i]);
    //     }
    //     if (sum < ansVal) {
    //         ans    = arr1;
    //         ansVal = sum;
    //     }
    // } while (next_permutation(all(arr1)));
    // for (int i = 0; i < c; i++) {
    //     cout << ans[i] << ' ';
    // }
    // cout << '\n';
    // cout << ansVal << '\n';
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n % 2) {  // 4 ~ 5 6 ~ 7
        for (int i = 0; i < n; i++) {
            if (arr[i] <= 3) {
                if (arr[i] == 1) {
                    cout << 2 << ' ';
                } else if (arr[i] == 2) {
                    cout << 3 << ' ';
                } else {
                    cout << 1 << ' ';
                }
                // assert(0);
            } else {
                if (arr[i] % 2 == 0) {
                    cout << arr[i] + 1 << ' ';
                } else {
                    cout << arr[i] - 1 << ' ';
                }
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 1) {
                cout << arr[i] + 1 << ' ';
            } else {
                cout << arr[i] - 1 << ' ';
            }
        }
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */