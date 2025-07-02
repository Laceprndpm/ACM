#include <algorithm>
#include <cmath>
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

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> factor;
    for (int i = 1; i <= sqrt(m); i++) {
        if (m % i == 0) {
            factor.push_back(i);
            factor.push_back(m / i);
        }
    }
    if (((int)(sqrt(m))) * ((int)sqrt(m)) == m) {
        factor.resize(factor.size() - 1);
    }
    sor(factor);
    int         num = sz(factor);
    vector<int> needs(num);
    auto        checkStep = [&](int idx, int gc) -> int {
        if (arr[idx] % gc > arr[idx + 1] % gc || (arr[idx] == gc - 1 && arr[idx + 1] % gc != arr[idx] % gc)) {
            return 1;
        }
        return 0;
    };
    for (int i = 0; i < num; i++) {
        int steps = 0;
        int gc    = factor[i];
        for (int j = 0; j < n - 1; j++) {
            if (checkStep(j, gc)) {
                steps++;
            }
        }
        needs[i] = steps;
    }

    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int place;
            int x;
            cin >> place >> x;
            place--;
            for (int j = 0; j < num; j++) {
                int oldsteps = 0;
                int gc       = factor[j];
                if (place - 1 >= 0) {
                    oldsteps += checkStep(place - 1, gc);
                }
                if (place + 1 < n) {
                    oldsteps += checkStep(place, gc);
                }

                needs[j] -= oldsteps;
            }
            arr[place] = x;
            for (int j = 0; j < num; j++) {
                int step = 0;
                int gc   = factor[j];
                if (place - 1 >= 0) {
                    step += checkStep(place - 1, gc);
                }
                if (place + 1 < n) {
                    step += checkStep(place, gc);
                }
                needs[j] += step;
            }
        } else {
            int k;
            cin >> k;
            int gc = gcd(k, m);
            int p  = find(all(factor), gc) - bg(factor);
            if (needs[p] < m / factor[p]) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    // 1 2 2 2 4 4 5
    // step = 1
    // 我感觉可以先对m进行因数分解
    // 假如有k个因数
    // 每次操作后，对于相连的区域进行合并/分裂操作
    // 相同的就缩点
    // 不同的就得考虑进了，要考虑是否要进，比如10 3 在mod 4就不需要进mod 3就得进
    //
}

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
        solve();
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