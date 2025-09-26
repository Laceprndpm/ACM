#include <bits/stdc++.h>
#define ll  long long
#define pb  push_back
#define u64 unsigned long long
using namespace std;
const int N       = 5.2e5 + 5;
const u64 MODBASE = 131;
u64       position_power[N], power_idx[N], prefix_pi[N];
ll        idx[N];
int       n, m, a[N];
string    s;

u64 qpow(u64 x, ll y)
{
    u64 z = 1;
    while (y) {
        if (y & 1) z *= x;
        x *= x, y >>= 1;
    }
    return z;
}

namespace Fen {
int num_1[N], fr;
u64 hash_arr[N];

void init()
{
    memset(num_1, 0, (n + 1) * 4);
    memset(hash_arr, 0, (n + 1) * 8);
}

void add(int x, int y, u64 val)
{
    for (; x <= n; x += x & -x) num_1[x] += y, hash_arr[x] += val;
}

u64 sum_hash(int r)
{
    u64 res = 0;
    for (; r; r -= r & -r) res += hash_arr[r];
    return res;
}

u64 sumT(int l, int r) { return sum_hash(r) - sum_hash(l - 1); }

int sum_num_1(int r)
{
    int res = 0;
    for (; r; r -= r & -r) res += num_1[r];
    return res;
}

int sumA(int l, int r) { return sum_num_1(r) - sum_num_1(l - 1); }

bool check(int L, int suma, u64 sumt)
{
    if (!suma) return true;
    int p2 = fr + suma - 1;
    u64 bb = prefix_pi[p2] - prefix_pi[fr - 1];  // fr 为第一个1前0的数量，p2为最后一个1前0的数量
    // init = 0
    // for (i, fr, p2 + 1):
    //     init += i
    //     hash1 += qpow(base, init)
    // 
    u64 tt = sumt;
    tt *= power_idx[fr];
    bb *= position_power[L + fr];
    return bb == tt;
}

int twopoint(int L)
{
    int x    = 0;
    int suma = -sum_num_1(L - 1);
    u64 sumt = -sum_hash(L - 1);
    for (int i = 31 - __builtin_clz(n); ~i; --i) {
        x ^= 1 << i;
        if (x > n || (x >= L && !check(L, suma + num_1[x], sumt + hash_arr[x])))
            x ^= 1 << i;
        else
            suma += num_1[x], sumt += hash_arr[x];
    }
    return x;
}

int two0(int L)
{
    int x    = 0;
    int suma = -sum_num_1(L - 1);
    for (int i = 31 - __builtin_clz(n); ~i; --i) {
        x ^= 1 << i;
        if (x > n || (x >= L - 1 && suma + num_1[x]))
            x ^= 1 << i;
        else
            suma += num_1[x];
    }
    return x - L + 1;
}
}  // namespace Fen

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    position_power[0] = 1;
    for (int i = 1; i < N; ++i) position_power[i] = position_power[i - 1] * MODBASE;
    idx[0] = 1;
    for (int i = 1; i < N; ++i) idx[i] = idx[i - 1] + i + 1;
    for (int i = 0; i < N; ++i) power_idx[i] = qpow(MODBASE, idx[i]);
    prefix_pi[0] = power_idx[0];
    for (int i = 1; i < N; ++i) prefix_pi[i] = prefix_pi[i - 1] + power_idx[i];
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin >> s;
        for (int i = 1; i <= n; ++i) a[i] = s[n - i] - '0';
        Fen::init();
        for (int i = 1; i <= n; ++i)
            if (a[i]) Fen::add(i, 1, position_power[i]);
        while (m--) {
            int opt;
            cin >> opt;
            if (opt == 1) {
                int l, r;
                cin >> r >> l;
                l = n - l + 1, r = n - r + 1;
                int fr  = 0;
                fr      = Fen::two0(l);
                Fen::fr = fr;
                if (l + fr > r) {
                    cout << "0\n";
                    continue;
                }
                int R = Fen::twopoint(l);
                if (R > r) R = r;
                int res = Fen::sumA(l, R);
                cout << res * 3 + fr - 3 << "\n";
            } else {
                int x;
                cin >> x;
                x = n - x + 1;
                a[x] ^= 1;
                if (a[x])
                    Fen::add(x, 1, position_power[x]);
                else
                    Fen::add(x, -1, -position_power[x]);
            }
        }
    }
    return 0;
}