#ifdef V1
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int          n, k;
constexpr LL MOD = 1e9;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    vector<bool> str(n);
    int          l = 0;
    int          r = n - 1;
    for (int i = 0; i < n; i++) {
        char input;
        cin >> input;
        if (input == 'E')
            str[i] = false;
        else
            str[i] = true;
    }
    if (n >= 3)
        while (k-- && l <= r) {
            while (str[l] && l <= r) {
                l++;
            }
            while (!str[r] && l <= r) {
                r--;
            }
            if (l >= r)
                break;
            str[l] = true;
            str[r] = false;
        }
    else {
        if (k % 2 != 0) {
            bool temp = str[1];
            str[1]    = str[0];
            str[0]    = temp;
        }
    }
    LL power = 1;
    LL ans   = 0;
    for (int i = 0; i < n; i++) {
        ans += power * (str[i] ? 1 : 0);
        ans %= MOD;
        power *= 2;
        power %= MOD;
    }
    cout << ans;
    return 0;
}

#endif

#ifdef std
char str[5];

signed main(signed argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n = init(), k = init();
    for (int i = 1; i <= n; ++i) {
        memset(str, 0, sizeof(str));
        scanf("%s", str + 1);
        a[i] = Str(str + 1);
    }
    int j = n;
    for (int i = 1; i <= n && k > 0; ++i) {
        if (!a[i]) {
            while (!a[j] && j >= i)
                j--;
            if (j < i || !a[j])
                break;  // 找不到 'O'
            a[i] = 1;
            a[j] = 0;
            --k;  // 进行有效交换
        }
    }
    if (n == 2 && k % 2 == 1)
        a[1] ^= a[2] ^= a[1] ^= a[2];  // 强制交换，其余 n >= 3 根据鸽巢原理必有至少两个相同元素，无尽换即可
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i])
            ans = (ans + quick_mod(2, i - 1)) % Mod;
    print(ans), putchar('\n');
    return 0;
}
#endif