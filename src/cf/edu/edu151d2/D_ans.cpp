#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

int main(int argc, char** argv)
{
    long long t, n, a, mx, cur, u, i, g, w;
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // cin >> t;
    // while (t--) {
    cin >> n;
    vector<int> arr(n + 1);
    cur = 0, mx = 0, u = 0, w = 0;
    for (i = 1; i <= n; i++) {
        cin >> a;
        arr[i] = a;
        cur += a;
        if (cur > mx) mx = cur;
        g = mx - cur;
        if (g > u) {
            u = g;
            w = mx;
        }
    }
    i64 total = 0;
    int ache = 0;
    for (int i = 1; i <= n; i++) {
        if (total >= w) {
            ache = true;
        }
        int a = arr[i];
        total += a;
        if (total < w && ache) {
            total = w;
        }
    }
    cout << total;
    return 0;
}