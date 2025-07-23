#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace fastio {
const int SZ = 1 << 16;
char      ibuf[SZ], *ip = ibuf + SZ;

inline char gc()
{
    if (ip == ibuf + SZ) {
        fread(ibuf, 1, SZ, stdin);
        ip = ibuf;
    }
    return *ip++;
}

template <typename T>
inline void read(T &x)
{
    x     = 0;
    int c = gc();
    while (c < '0')
        c = gc();
    for (; c >= '0'; c = gc())
        x = x * 10 + (c & 15);
}

char obuf[SZ];
int  op = 0;

inline void pc(char c)
{
    if (op == SZ) {
        fwrite(obuf, 1, SZ, stdout);
        op = 0;
    }
    obuf[op++] = c;
}

inline void flush()
{
    fwrite(obuf, 1, op, stdout);
}

inline void write_u64(uint64_t x)
{
    char s[24];
    int  n = 0;
    if (!x) s[n++] = '0';
    while (x) {
        s[n++] = char('0' + (x % 10));
        x /= 10;
    }
    while (n--)
        pc(s[n]);
    pc('\n');
}
}  // namespace fastio

using fastio::flush;
using fastio::pc;
using fastio::read;
using fastio::write_u64;

int                n, mid;
unsigned long long a[55];

const int          MAXR = 200000;
unsigned long long vec[MAXR];
int                vsz;

void dfsr(int idx, bool prev, bool FS, bool needFS, unsigned long long x)
{
    if (idx == n) {
        if (FS == needFS) vec[vsz++] = x;
        return;
    }
    dfsr(idx + 1, false, FS, needFS, x);
    if (!prev) {
        bool fs = FS || (idx == mid);
        dfsr(idx + 1, true, fs, needFS, x ^ a[idx]);
    }
}

const unsigned long long *Rptr;
int                       Rlen, need, cur;
unsigned long long        want;

bool dfsl(int idx, bool prev, unsigned long long x)
{
    if (idx == mid) {
        if (prev != need) return false;
        unsigned long long p    = x >> cur;
        unsigned long long tgt  = p ^ want;
        unsigned long long low  = tgt << cur;
        unsigned long long high = cur ? (low | ((1ULL << cur) - 1)) : low;
        auto               it   = std::lower_bound(Rptr, Rptr + Rlen, low);
        return it != Rptr + Rlen && *it <= high;
    }
    if (dfsl(idx + 1, false, x)) return true;
    return (!prev) && dfsl(idx + 1, true, x ^ a[idx]);
}

unsigned long long solve(const unsigned long long *R, int len, int needLS)
{
    if (len == 0) return 0;
    Rptr                   = R;
    Rlen                   = len;
    unsigned long long ans = 0;
    for (int bit = 60; bit >= 0; --bit) {
        cur  = bit;
        want = (ans | (1ULL << bit)) >> bit;
        need = needLS;
        if (dfsl(0, false, 0)) ans |= (1ULL << bit);
    }
    return ans;
}

int main()
{

    int TT;
    read(TT);

    while (TT--) {
        read(n);
        for (int i = 0; i < n; i++)
            read(a[i]);
        mid = n / 2;

        unsigned long long ans = 0;

        vsz = 0;
        dfsr(mid, false, false, false, 0);
        std::sort(vec, vec + vsz);
        ans = std::max(ans, solve(vec, vsz, 0));
        ans = std::max(ans, solve(vec, vsz, 1));

        vsz = 0;
        dfsr(mid, false, false, true, 0);
        std::sort(vec, vec + vsz);
        ans = std::max(ans, solve(vec, vsz, 0));

        write_u64(ans);
    }
    flush();
    return 0;
}
