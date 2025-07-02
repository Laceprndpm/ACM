#include <algorithm>
#include <iostream>
#include <stack>
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
constexpr int MAX = 2e5 + 5;

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
    vector<string>                 svec;
    vector<int>                    version(MAX);
    vector<vector<int>>            serverAdd(MAX);
    vector<pair<int, vector<int>>> pc(n);
    int                            versionPtr = 0;
    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        if (cur == 1) {
            int p;
            cin >> p;
            p--;
            pc[p] = {versionPtr, {}};
        } else if (cur == 2) {
            int    p;
            string s;
            cin >> p >> s;
            p--;
            svec.push_back(s);
            pc[p].second.push_back(sz(svec) - 1);
        } else {
            int p;
            cin >> p;
            p--;
            version[++versionPtr] = pc[p].first;
            serverAdd[versionPtr] = std::move(pc[p].second);
            pc[p].first           = versionPtr;
            pc[p].second          = {};
        }
    }
    vector<int> sta;
    while (versionPtr) {
        sta.insert(sta.end(), serverAdd[versionPtr].rbegin(), serverAdd[versionPtr].rend());
        versionPtr = version[versionPtr];
    }
    sta.insert(sta.end(), serverAdd[versionPtr].rbegin(), serverAdd[versionPtr].rend());
    reverse(all(sta));
    for (int i : sta) {
        cout << svec[i];
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