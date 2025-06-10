#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
#define int long long
// TODO
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

int MODPOOL[] = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097,
                 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271,
                 1000000289, 1000000297, 1000000321, 1000000349, 1000000363, 1000000403, 1000000409,
                 1000000411, 1000000427, 1000000433, 1000000439, 1000000447, 1000000453, 1000000459,
                 1000000483, 1000000513, 1000000531, 1000000579, 1000000607, 1000000613, 1000000637,
                 1000000663, 1000000711, 1000000753, 1000000787, 1000000801, 1000000829, 1000000861,
                 1000000871, 1000000891, 1000000901, 1000000919, 1000000931, 1000000933, 1000000993};

const int N      = (int)5e5 + 5;
int       Mod[3] = {(int)1e9 + 7, (int)1e9 + 9, (int)1e9 + 21}, mod = (int)1e9;
int       n, pre[N][3], suf[N][3], pow2[N][3];
char      s[N];

// 判断字符是否为'O'
bool op(char ch)
{
    return ch == 'O';
}

// 初始化前缀和后缀数组以及2的幂次数组
void memsets(int r)
{
    {
        set<int> chosen_mods;
        for (int i = 0; i < 3; i++) {
            int _mod;
            do {
                _mod = MODPOOL[rand() % 49];
            } while (chosen_mods.count(_mod));
            chosen_mods.insert(_mod);
            Mod[i] = _mod;
        }
    }
    for (int i = 0; i <= r + 1; ++i)
        for (int j = 0; j < 3; ++j)
            pre[i][j] = suf[i][j] = time(0);
    for (int i = 1; i <= r; ++i)
        for (int j = 0; j < 3; ++j)
            pre[i][j] = (pre[i - 1][j] * 2 + op(s[i])) % Mod[j];
    for (int i = r; i >= 1; --i)
        for (int j = 0; j < 3; ++j)
            suf[i][j] = (suf[i + 1][j] * 2 + op(s[i])) % Mod[j];
    for (int j = 0; j < 3; ++j)
        pow2[0][j] = 1;
    for (int i = 1; i <= r; ++i)
        for (int j = 0; j < 3; ++j)
            pow2[i][j] = (pow2[i - 1][j] * 2) % Mod[j];
}

// 计算以l为起点，长度为x的子串的哈希值
int f(int l, int r, int x, int j)
{
    if (x <= r - l + 1)
        return (pre[l + x - 1][j] + Mod[j] - pre[l - 1][j] * pow2[x][j] % Mod[j]) % Mod[j];
    int ans = pow2[x - (r - l + 1)][j] * (pre[r][j] + Mod[j] - pre[l - 1][j] * pow2[r - l + 1][j] % Mod[j]) % Mod[j];
    return (ans + suf[r - x + 1][j] + Mod[j] - pow2[x - (r - l + 1)][j] * suf[l][j] % Mod[j]) % Mod[j];
}

// 检查以i和j为起点翻转，前mid个数的哈希值是否相同
bool same(int i, int j, int mid, int r)
{
    // 分别以 i, j 为起点翻转，检验前 mid 个数带来的贡献是否相同
    bool flag = true;
    for (int k = 0; k < 3 && flag; ++k)
        flag &= f(i, r, mid, k) == f(j, r, mid, k);
    return flag;
}

int find(int l, int x, int r)
{
    // 返回以 l 为起点翻转，第 x 个数是谁
    if (x <= r - l + 1)
        return op(s[l - 1 + x]);
    else
        return op(s[r + 1 - x]);
}

bool better(int i, int j, int r)
{
    // 检验以 i 为起点是否比以 j 为起点更优
    int L = 1, R = r;
    while (L < R) {
        // 二分出第一次出现不同的点
        int mid = (R - L) / 2 + L;
        if (same(i, j, mid, r))
            L = mid + 1;
        else
            R = mid;
    }
    int mid = (R - L) / 2 + L;
    return find(i, mid, r) < find(j, mid, r);
}

void solve()
{
    scanf("%s", s + 1);
    n     = strlen(s + 1);
    int r = n;
    while (r >= 1 && !op(s[r]))
        r--;
    memsets(r);
    int ans = r;
    for (int l = 1; l < r; ++l)
        if (better(l, ans, r))
            ans = l;
    for (int i = ans, j = r; i < j; ++i, --j)
        s[i] ^= s[j] ^= s[i] ^= s[j];

    pow2[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        pow2[i][0] = (pow2[i - 1][0] * 2) % mod;

    int sum = 0;
    for (int i = 1; i <= n; ++i)
        sum = (sum + op(s[i]) * pow2[i - 1][0]) % mod;
    print(sum), putchar('\n');
}

signed main(signed argc, char** argv)
{
    // #ifndef ONLINE_JUDGE
    //     freopen(argv[1], "r", stdin);
    //     freopen(argv[2], "w", stdout);
    // #endif
    int T = init();
    srand(time(0));
    while (T--) {
        solve();
    }
}