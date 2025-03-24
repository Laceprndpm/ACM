#include <unordered_map>
#include <unordered_set>
#define REMOVE_ME
#include <iostream>
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
    unordered_set<int> s;

    // for (int j = 1; j <= 20; j++) {
    //     s.insert((j + 1) * j / 2);
    // }
    // for (int i = 1; i <= 1e2; i++) {
    //     cout << i << ' ';
    //     if (s.contains(i)) {
    //         cout << '\n';
    //     }
    // }
    // return 0;
    int cur = 1;
    for (int i = 1; i <= 19; i++) {
        cur += i * 4;
        cout << i << ' ' << cur << '\n';
    }
}

// 1 5 13 25 41 61
// 4 8 12 16 20