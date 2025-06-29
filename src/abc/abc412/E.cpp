#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using i128 = __int128;
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
#define i64 i128

struct Prime {
    vector<int> minp, primes;

    Prime(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();

        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                if (p == minp[i]) {
                    break;
                }
            }
        }
    }
};

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    Prime p(1e7);
    u64   L, R;
    cin >> L >> R;
    vector<int> delta(R - L + 1);
    if (L == 1) {
        delta[0] = 1;
    }
    for (int p : p.primes) {  // de-k * p
        i64 st = (L + p - 1) / p * p;
        while (st <= R) {
            delta[st - L] = 1;
            st += p;
        }
    }
    i64  ans  = 0;
    bool flag = 0;
    for (int p : p.primes) {  // add p ** k
        i128 prime_k = p;
        while (prime_k < L) {
            prime_k *= p;
        }
        if (prime_k == L) flag = 1;
        while (prime_k <= R) {
            prime_k *= p;
            ans++;
        }
    }
    for (int i = 0; i <= R - L; i++) {
        if (!delta[i]) {
            ans++;
        }
    }
    if (delta[0] == 0) {
        flag = 1;
    }
    ans += !flag;
    cout << (u64)ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */