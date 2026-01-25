#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

constexpr int INF = 1e9;

void lzhsb()
{
    int n;
    cin >> n;
    vector<int> arr(1 << n);
    iota(all(arr), 0);
    sort(all(arr), [](int a, int b) {
        int ra = ~a, rb = ~b;
        ra = ra & -ra, rb = rb & -rb;
        return ra == rb ? a < b : ra > rb;
    });
    for (int i : arr) cout << i << " \n"[i == arr.back()];
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        lzhsb();
    }
    return 0;
}
