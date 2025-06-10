#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL MOD = 1e9 + 7;
LL pow2(int q)
{
    if (q == 0)
    {
        return 1;
    }
    LL ans = 1;
    LL n = 2;
    while (q > 0)
    {
        if (q & 1)
        {
            ans *= n;
            ans %= MOD;
        }
        n *= n;
        n %= MOD;
        q >>= 1;
    }
    return ans;
}

void solve(void)
{
    int n, k;
    cin >> n >> k; // n个, k位
    if (n % 2 == 0)
    {
        // 前面已经赢了的情况：
        LL prewin = 0;
        // 前面一直相等的情况：
        LL preequal = 1;
        for (int i = 1; i <= k; i++)
        {
            // 这一位相等的情况：
            // (1,1) or (0,0)
            // (1,1)，偶数不可能
            // (0,0)，只要有偶数个1即可，即0Cn，2Cn，4Cn...(n-2)Cn = 2 ^ (n-1) - 1
            LL num_equal = pow2(n - 1) - 1;
            // 这一位获胜的情况：
            // (1,0) 全部为1
            LL num_win = 1;
            // 这一位总共赢了的数量
            LL win = prewin * pow2(n);
            win %= MOD;
            win += preequal * num_win;
            win %= MOD;
            // 这一位依然平局的可能性
            LL equal = preequal * num_equal;
            equal %= MOD;
            // 进入下一局
            prewin = win;
            preequal = equal;
        }
        cout << ((prewin + preequal) % MOD + MOD) % MOD << '\n';
    }
    else
    {
        // 前面一直相等的情况：
        LL preequal = 1;
        for (int i = 1; i <= k; i++)
        {

            // 这一位相等的情况：
            // (1,1) or (0,0)
            // (1,1)，为全1
            // (0,0)，只要有偶数个1即可，即0Cn，2Cn，4Cn...(n-3)Cn = 2 ^ (n-1)
            LL num_equal = pow2(n - 1) + 1;

            // 这一位总共赢了的数量
            // 没法赢
            // 这一位依然平局的可能性
            LL equal = preequal * num_equal;
            equal %= MOD;
            // 进入下一局
            preequal = equal;
        }
        cout << ((preequal) % MOD + MOD) % MOD << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}