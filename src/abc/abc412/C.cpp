#include <algorithm>
#include <iostream>
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

signed main(signed argc, char** argv)
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
    while (t--) {
        int n;
        cin >> n;
        vector<int> vec(n);
        for (int i = 0; i < n; i++) {
            cin >> vec[i];
        }
        sort(vec.begin() + 1, vec.end() - 1);
        int j      = 0;
        int time   = 2;
        int curval = vec[0];
        while (curval * 2 < vec[n - 1]) {
            time++;
            if (curval * 2 >= vec[j + 1]) {
                while (j + 1 < n && curval * 2 >= vec[j + 1]) {
                    j++;
                }
                curval = vec[j];
            } else {
                break;
            }
        }
        if (curval * 2 >= vec[n - 1]) {
            cout << time << '\n';
        } else {
            cout << -1 << '\n';
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