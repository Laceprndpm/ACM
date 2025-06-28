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
    int q, n;
    cin >> n >> q;
    vector<int> arr(q);
    for (int i = 0; i < q; i++) {
        cin >> arr[i];
    }
    vector<int> box(n + 1);
    for (int i = 0; i < q; i++) {
        if (arr[i] == 0) {
            auto it = min_element(bg(box) + 1, box.end());
            arr[i]  = it - bg(box);
            (*it)++;
        } else {
            box[arr[i]]++;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << arr[i] << ' ';
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