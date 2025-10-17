#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 10000005;
const int INF  = 1000000005;

bool is_prime[MAXN];

inline int calc_v(int p, int x)
{
    int res  = 0;
    ll  pw_p = p;
    while (pw_p <= x) {
        res += x / pw_p;
        pw_p *= p;
    }
    return res;
}

int         t;
int         n, m;
vector<int> small_primes;

int main()
{
#ifndef DEBUG
    ios::sync_with_stdio(0), cin.tie(0);
#endif
    for (int i = 2; i < MAXN; i++) {
        is_prime[i] = true;
    }
    for (int p = 2; (ll)p * p < MAXN; p++) {
        if (!is_prime[p]) {
            continue;
        }
        small_primes.push_back(p);
        for (int i = p * p; i < MAXN; i += p) {
            is_prime[i] = false;
        }
    }

    cin >> t;
    while (t--) {
        cin >> n >> m;

        // find largest prime q <= n. Requires at most 142 iterations (due to
        // prime gap)
        int q = n;
        while (!is_prime[q]) {
            q--;
        }

        // precompute the useful big primes
        vector<int> useful_p;
        for (int f = 1; (ll)f * f <= n; f++) {
            // p_bnd is the largest possible value such that floor(n / p_bnd) =
            // f n / p_bnd >= f p_bnd <= n / f
            // 
            // 即：p_bnd 是满足 floor(n / p_bnd) = f 的最大值
            int p_bnd = n / f;
            int p     = p_bnd;
            while (!is_prime[p]) {
                p--;
            }
            useful_p.push_back(p);
        }

        ll ans = 0;
        // for all x < q, f_m(x, n) = 0. try all x >= q
        for (int x = q; x < n; x++) {
            int res = INF;

            for (int p : useful_p) {
                int vx = calc_v(p, x), vn = calc_v(p, n);
                if (vx != vn) {
                    res = min(res, vx);
                }
            }

            for (int p : small_primes) {
                if ((ll)p * p > m) {
                    break;
                }

                int base_vx = calc_v(p, x), base_vn = calc_v(p, n);
                for (ll exp = 1, pw_p = p; pw_p <= m; exp++, pw_p *= p) {
                    int vx = base_vx / exp, vn = base_vn / exp;
                    if (vx != vn) {
                        res = min(res, vx);
                    }
                }
            }

            ans += res;
        }

        cout << ans << '\n';
    }
    return 0;
}
