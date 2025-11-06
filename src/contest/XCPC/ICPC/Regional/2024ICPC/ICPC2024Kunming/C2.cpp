#include <cstdint>
#include <iostream>

using namespace std;

uint64_t invs[1 << 19];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 1; i < size(invs); ++i) invs[i] = -1ull / 2 / i;
    for (int tc = (cin >> tc, tc); tc--;) {
        uint64_t n, k, a{}, s{1};
        cin >> n >> k;
        if (k >= n) {
            cout << n << '\n';
            continue;
        }
        if (2 * k >= n) {
            cout << n - (n - k & 1) << '\n';
            continue;
        }
        a = --k, s = 1;
        uint64_t kk = max(min(k < 1 ? 0 : (k - 1) * __int128_t(k - 1), {n - 2 * k}), {});
        if (a < kk) {
            uint64_t r = a * __uint128_t(-1ull / s) >> 64;
            ++r;
            auto p = r * s, q = k * s;
            if (p <= a)
                a += q - p;
            else
                a += q - p + s;
            ++s;
        }
        while (a < kk) {
            uint64_t is = -1ull / (s + 1);
            {
                uint64_t r = a * __uint128_t(invs[s / 2]) >> 64;
                ++r;
                auto p = r * s, q = k * s;
                if (p <= a)
                    a += q - p;
                else
                    a += q - p + s;
                ++s;
            }
            {
                uint64_t r = a * __uint128_t(is) >> 64;
                ++r;
                auto p = r * s, q = k * s;
                if (p <= a)
                    a += q - p;
                else
                    a += q - p + s;
                ++s;
            }
        }
        if (a >= n)
            a -= (a - n + s - 1) / (s - 1) * (s - 1);
        else
            while (1) {
                s      = a / k + 1;
                auto t = (min(k * s, n) - a + s - 1) / s;
                a += s * t;
                if (a >= n) {
                    a -= s;
                    break;
                }
            }
        cout << a + 1 << '\n';
    }
}
