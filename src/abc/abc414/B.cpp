#include <iostream>
#include <utility>
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
    int n;
    cin >> n;
    i64                     totallen = 0;
    bool                    fail     = 0;
    vector<pair<char, i64>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
        totallen += vec[i].second;
        if (totallen > 100 || vec[i].second > 100) {
            fail = 1;
        }
    }
    if (fail) {
        cout << "Too Long\n";
        return 0;
    }
    for (auto i : vec) {
        for (int j = 0; j < i.second; j++) {
            cout << i.first;
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