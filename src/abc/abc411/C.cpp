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
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    int         num = 0;
    for (int i = 0; i < q; i++) {
        int p;
        cin >> p;
        p--;
        bool flg  = 1;
        bool flg2 = 0;
        if (p != 0) {
            if (vec[p - 1] != 1) {
                flg = 0;
            } else {
                flg2 = 1;
            }
        } else {
            flg = 0;
        }
        if (p + 1 < n) {
            if (vec[p + 1] != 1) {
                flg = 0;
            } else {
                flg2 = 1;
            }
        } else {
            flg = 0;
        }

        if (flg) {
            if (vec[p]) {
                num++;
            } else {
                num--;
            }
        } else if (!flg2) {
            if (vec[p]) {
                num--;
            } else {
                num++;
            }
        } else {
        }
        vec[p] = !vec[p];
        cout << num << '\n';
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