#include <cassert>
#include <cstdio>
#include <cstring>
#define int long long

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x / 10)
        print(x / 10);
    putchar(x % 10 + '0');
}

const int N = (int)2e6 + 5, Mod = (int)1e9 + 7;
char      s[N];
int       sum[N], pow10[N], bel[N], nxt1[N], nxt2[N], pre1[N], pre2[N], mul[N], len;

int Sum(int l, int r)
{
    return (sum[r] - sum[l - 1] * pow10[r - l + 1] % Mod + Mod) % Mod;
}

int mn(int x, int y)
{
    return x < y ? x : y;
}

int Nxt(int i, int tp)
{
    if (tp == 1)
        return nxt1[i];
    if (tp == 2)
        return nxt2[i];
    return mn(nxt1[i], nxt2[i]);
}

int Pre(int i, int tp)
{
    if (tp == 1)
        return pre1[i];
    if (tp == 2)
        return pre2[i];
    return mn(pre1[i], pre2[i]);
}

void Relax(int& x, int y)
{
    x = x + y >= Mod ? x + y - Mod : x + y;
}

int quick_mod(int x, int y)
{
    int s = 1;
    while (y) {
        if (y & 1)
            s = s * x % Mod;
        x = x * x % Mod;
        y >>= 1;
    }
    return s;
}

int Mul(int l, int r)
{
    return mul[r] * quick_mod(mul[l - 1], Mod - 2) % Mod;
}

int belong[N], cal[N];

int calc(int l, int r)
{
    return cal[r] >= cal[l - 1] ? cal[r] - cal[l - 1] : cal[r] - cal[l - 1] + Mod;
}

void _memset()
{
    len = strlen(s + 1);
    for (int i = 1; i <= len; ++i)
        s[i + len] = s[i];
    pow10[0] = 1;
    for (int i = 1; i <= (len << 1); ++i)
        pow10[i] = ((pow10[i - 1] << 1) + (pow10[i - 1] << 3)) % Mod;
    for (int i = 1; i <= (len << 1); ++i)
        if (s[i - 1] == '+' || s[i - 1] == '*')
            sum[i] = s[i] - '0';
        else if ('0' <= s[i] && s[i] <= '9')
            sum[i] = ((sum[i - 1] << 1) + (sum[i - 1] << 3) + s[i] - '0') % Mod;
    for (int i = 1; i <= (len << 1); ++i)
        if (s[i - 1] < '0' || s[i - 1] > '9')
            bel[i] = ++bel[0];
        else
            bel[i] = bel[i - 1];
    nxt1[len << 1 | 1] = nxt2[len << 1 | 1] = len << 1 | 1;
    for (int i = len << 1; i >= 1; --i)
        if (s[i] == '+')
            nxt1[i] = i, nxt2[i] = nxt2[i + 1];
        else if (s[i] == '*')
            nxt2[i] = i, nxt1[i] = nxt1[i + 1];
        else
            nxt1[i] = nxt1[i + 1], nxt2[i] = nxt2[i + 1];
    pre1[0] = pre2[0] = 0;
    for (int i = 1; i <= (len << 1); ++i)
        if (s[i] == '+')
            pre1[i] = i, pre2[i] = pre2[i - 1];
        else if (s[i] == '*')
            pre2[i] = i, pre1[i] = pre1[i - 1];
        else
            pre1[i] = pre1[i - 1], pre2[i] = pre2[i - 1];
    for (int i = 1; i <= (len << 1); ++i)
        if (s[i] == '+' || s[i] == '*')
            if (bel[i - 1] == 1)
                mul[1] = Sum(1, i - 1);
            else {
                int j           = Pre(i - 1, 0);
                mul[bel[i - 1]] = mul[bel[j - 1]] * Sum(j + 1, i - 1) % Mod;
            }
    int j              = Pre(len << 1, 0);
    mul[bel[len << 1]] = mul[bel[j - 1]] * Sum(j + 1, len << 1) % Mod;
    belong[bel[1]]     = ++belong[0];
    for (int i = 2; i <= (len << 1); ++i)
        if (s[i] == '+') {
            int j              = Pre(i - 1, 1);
            cal[belong[0]]     = (cal[belong[0] - 1] + Mul(bel[j + 1], bel[i - 1])) % Mod;
            belong[bel[i + 1]] = ++belong[0];
        } else
            belong[bel[i]] = belong[0];
}

signed main(signed argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    scanf("%s", s + 1);
    _memset();
    int cnt = 0;
    for (int i = 1; i <= len; ++i)
        cnt += (s[i] == '+' || s[i] == '*');
    if (cnt == 0) {
        int ans = 0;
        for (int i = 1; i <= len; ++i)
            Relax(ans, Sum(i, i + len - 1));
        print(ans), putchar('\n');
        return 0;
    }
    if (cnt == 1) {
        int ans = 0;
        for (int i = 1; i <= len; ++i) {
            if (s[i] == '+' || s[i] == '*')
                continue;
            int j = i + len - 1;
            if (s[j] == '+' || s[j] == '*')
                continue;
            int op = Nxt(i, 0);
            if (s[op] == '+')
                Relax(ans, (Sum(i, op - 1) + Sum(op + 1, j)) % Mod);
            else
                Relax(ans, (Sum(i, op - 1) * Sum(op + 1, j)) % Mod);
        }
        print(ans), putchar('\n');
        return 0;
    }
    cnt = 0;
    for (int i = 1; i <= len; ++i)
        cnt += (s[i] == '+');
    if (cnt == 0) {
        int ans = 0;
        for (int i = 1; i <= len; ++i) {
            if (s[i] == '+' || s[i] == '*')
                continue;
            int j = i + len - 1;
            if (s[j] == '+' || s[j] == '*')
                continue;
            int op1 = Nxt(i, 0), op2 = Pre(j, 0);
            Relax(ans, Sum(i, op1 - 1) * Sum(op2 + 1, j) % Mod * Mul(bel[op1 + 1], bel[op2 - 1]) % Mod);
        }
        print(ans), putchar('\n');
        return 0;
    }
    if (cnt == 1) {
        int ans = 0;
        for (int i = 1; i <= len; ++i) {
            if (s[i] == '+' || s[i] == '*')
                continue;
            int j = i + len - 1;
            if (s[j] == '+' || s[j] == '*')
                continue;
            int op = Nxt(i, 1);
            int s1 = 0, s2 = 0;
            int op1 = Nxt(i, 2), op2 = Pre(op - 1, 2);
            if (op1 > op - 1)
                s1 = Sum(i, op - 1);
            else if (op1 == op2)
                s1 = Sum(i, op1 - 1) * Sum(op2 + 1, op - 1) % Mod;
            else
                s1 = Sum(i, op1 - 1) * Sum(op2 + 1, op - 1) % Mod * Mul(bel[op1 + 1], bel[op2 - 1]) % Mod;
            op1 = Nxt(op + 1, 2), op2 = Pre(j, 2);
            if (op1 > j)
                s2 = Sum(op + 1, j);
            else if (op1 == op2)
                s2 = Sum(op + 1, op1 - 1) * Sum(op2 + 1, j) % Mod;
            else
                s2 = Sum(op + 1, op1 - 1) * Sum(op2 + 1, j) % Mod * Mul(bel[op1 + 1], bel[op2 - 1]) % Mod;
            Relax(ans, s1 + s2 >= Mod ? s1 + s2 - Mod : s1 + s2);
        }
        print(ans), putchar('\n');
        return 0;
    }
    int ans = 0;
    for (int i = 1; i <= len; ++i) {
        if (s[i] == '+' || s[i] == '*')
            continue;
        int j = i + len - 1;
        if (s[j] == '+' || s[j] == '*')
            continue;
        int op1 = Nxt(i, 1), op2 = Pre(j, 1);
        int first = 0, last = 0;
        {
            int op3 = Nxt(i, 2), op4 = Pre(op1 - 1, 2);
            if (op3 > op1 - 1)
                first = Sum(i, op1 - 1);
            else if (op3 == op4)
                first = Sum(i, op3 - 1) * Sum(op4 + 1, op1 - 1) % Mod;
            else
                first = Sum(i, op3 - 1) * Sum(op4 + 1, op1 - 1) % Mod * Mul(bel[op3 + 1], bel[op4 - 1]) % Mod;
        }
        {
            int op3 = Nxt(op2 + 1, 2), op4 = Pre(j, 2);
            if (op3 > j)
                last = Sum(op2 + 1, j);
            else if (op3 == op4)
                last = Sum(op2 + 1, op3 - 1) * Sum(op4 + 1, j) % Mod;
            else
                last = Sum(op2 + 1, op3 - 1) * Sum(op4 + 1, j) % Mod * Mul(bel[op3 + 1], bel[op4 - 1]) % Mod;
        }
        Relax(ans, (first + last + calc(belong[bel[op1 + 1]], belong[bel[op2 - 1]])) % Mod);
    }
    print(ans), putchar('\n');
}
