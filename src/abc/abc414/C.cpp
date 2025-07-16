#include <algorithm>
#include <iostream>
#include <string>
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
    int a;
    cin >> a;
    i64 n;
    cin >> n;
    auto judge = [&](i64 s) -> bool {
        if (s > n) return 0;
        string tmp;
        while (s) {
            tmp.pb((char)(s % a + '0'));
            s /= a;
        }
        for (int i = 0, j = tmp.size() - 1; i <= j; i++, j--) {
            if (tmp[i] != tmp[j]) {
                return 0;
            }
        }
        return 1;
    };
    i64         ans = 0;
    for (int mid = 0; mid < 10; mid++) {
        i64 val2 = mid;
        if (judge(val2)) {
            ans += val2;
        }
    }
    for (int i = 1; i < 1e6; i++) {
        string s  = to_string(i);
        string rs = s;
        reverse(all(rs));
        i64 val1 = stoll(s + rs);
        if (judge(val1)) {
            ans += val1;
        }
        if (s.length() <= 5) {
            for (int mid = 0; mid < 10; mid++) {
                i64 val2 = stoll(s + to_string(mid) + rs);
                if (judge(val2)) {
                    ans += val2;
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */