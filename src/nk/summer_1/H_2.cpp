#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using u128 = unsigned __int128;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u8   = unsigned char;
// vectors
#define len(x)  int(x.size())
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
// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

template <typename T>
T floor(T a, T b)
{
    return a / b;
}

template <typename T>
T ceil(T x, T y)
{
    return floor(x + y - 1, y);
}

struct My_Bitset {
    int         N;
    vector<u64> dat;
    using T = My_Bitset;

    My_Bitset(int N = 0, int x = 0) : N(N)
    {
        assert(x == 0 || x == 1);
        u64 v = (x == 0 ? 0 : -1);
        dat.assign((N + 63) >> 6, v);
        if (N) dat.back() >>= (64 * len(dat) - N);
    }

    static T from_string(string &S)
    {
        int N = len(S);
        T   ANS(N);
        for (int i = 0; i < N; i++)
            ANS[i] = (S[i] == '1');
        return ANS;
    }

    int size()
    {
        return N;
    }

    // thanks to chatgpt!
    class Proxy {
    public:
        Proxy(vector<u64> &d, int i) : dat(d), index(i) {}

        operator bool() const
        {
            return (dat[index >> 6] >> (index & 63)) & 1;
        }

        Proxy &operator=(u64 value)
        {
            dat[index >> 6] &= ~(u64(1) << (index & 63));
            dat[index >> 6] |= (value & 1) << (index & 63);
            return *this;
        }

        void flip()
        {
            dat[index >> 6] ^= (u64(1) << (index & 63));  // XOR to flip the bit
        }

    private:
        vector<u64> &dat;
        int          index;
    };

    Proxy operator[](int i)
    {
        return Proxy(dat, i);
    }

    My_Bitset range(int L, int R)
    {
        assert(L <= R);
        My_Bitset p(R - L);
        int       rm = (R - L) & 63;
        for (i64 _ = 0; _ < rm; _++) {
            p[R - L - 1] = bool((*this)[R - 1]);
            --R;
        }
        int n  = (R - L) >> 6;
        int hi = L & 63;
        int lo = 64 - hi;
        int s  = L >> 6;
        if (hi == 0) {
            for (i64 i = 0; i < n; i++) {
                p.dat[i] ^= dat[s + i];
            }
        } else {
            for (i64 i = 0; i < n; i++) {
                p.dat[i] ^= (dat[s + i] >> hi) ^ (dat[s + i + 1] << lo);
            }
        }
        return p;
    }

    T &operator^=(const T &p)
    {
        assert(N == p.N);
        for (int i = 0; i < len(dat); i++)
            dat[i] ^= p.dat[i];
        return *this;
    }

    void flip(int i)
    {
        (*this)[i].flip();
    }

    T operator^(const T &p) const
    {
        return T(*this) ^= p;
    }
};

struct T {
    i64 hi, curans, through, lo;
};

struct Mono {
    using value_type = T;
    using X          = value_type;

    static X op(X L, X R)
    {
        swap(L, R);
        // c是through
        // a是前缀
        // b是答案
        // d是后缀

        return T{L.hi + R.hi * L.through, L.curans + R.hi * L.lo + R.curans, R.through * L.through,
                 R.through * L.lo + R.lo};
    }

    static constexpr X unit()
    {
        return T{0, 0, 1, 0};
    }

    static constexpr bool commute = 0;
};

T dat[1 << 16];
T t0;
T t1;

void init()
{
    t0 = {1, 1, 1, 1};
    t1 = {0, 0, 0, 0};

    dat[0] = Mono::unit();
    for (int i = 0; i < 16; i++) {
        for (int s = 0; s < (1ll << i); s++) {
            T t             = dat[s];
            dat[s]          = Mono::op(t, t0);
            dat[s | 1 << i] = Mono::op(t, t1);
        }
    }
}

void app(const T &L, T &R)
{
    R = Mono::op(L, R);
}

signed main(signed argc, char **argv)
{
    init();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int N, q;
    cin >> N >> q;
    string s;
    cin >> s;
    My_Bitset bitst(N);
    for (int i = 0; i < N; i++) {
        if (s[i] == '1') {
            bitst[i] = 1;
        }
    }
    auto work = [&](My_Bitset x) -> i64 {
        T   start = Mono::unit();
        i64 n     = len(x);
        while (n & 63) {
            if (x[n - 1]) {
                app(t1, start);
            } else {
                app(t0, start);
            }
            --n;
        }
        n /= 64;
        for (int i = n - 1; i >= 0; i--) {
            u64 u = x.dat[i];
            // FOR_R(i, 64) {
            //   if (u >> i & 1) {
            //     apply(t1, ANS);
            //   } else {
            //     apply(t0, ANS);
            //   }
            // }
            // continue;
            u64 u0 = u & 65535;
            u64 u1 = (u >> 16) & 65535;
            u64 u2 = (u >> 32) & 65535;
            u64 u3 = (u >> 48) & 65535;
            // // apply(dat[u3], ANS);
            // start = Mono::op(start, dat[u3]);
            // start = Mono::op(start, dat[u2]);
            // start = Mono::op(start, dat[u1]);
            // start = Mono::op(start, dat[u0]);
            app(dat[u3], start);
            app(dat[u2], start);
            app(dat[u1], start);
            app(dat[u0], start);
        }
        return start.curans;
    };
    vector<u64> block(1 << 15);
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            i64 l, r;
            cin >> l >> r;
            l--;
            while (l % 64 != 0 && l < r) {
                bitst.flip(l++);
            }
            while (r % 64 != 0 && l < r) {
                bitst.flip(--r);
            }
            block[r / 64] ^= 1;
            block[l / 64] ^= 1;
        } else {
            i64 n = ceil<i64>(N, 64);
            FOR(i, n)
            {
                block[i + 1] ^= block[i];
                bitst.dat[i] ^= -block[i];
                block[i] = 0;
            }
            i64 l, a, b;
            cin >> l >> a >> b;
            a--, b--;
            auto aa = bitst.range(a, a + l);
            auto bb = bitst.range(b, b + l);
            cout << work(aa ^ bb) << '\n';
        }
    }
    return 0;
}

// 0100
// 0010
//
// 0010
// 0100
//
//
// 1001001001
//
// 1110111001
//  23456
// 11011
// 11001
//

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */