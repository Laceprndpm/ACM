#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int MOD = 998244353;

int main()
{
    int k;
    scanf("%d", &k);
    vector<int> arr2seed(1 << k);
    for (int i = 0; i < 1 << k; i++) {
        scanf("%d", &arr2seed[i]);
        if (arr2seed[i] != -1) --arr2seed[i];
    }
    int ans = 1;
    for (int st = k - 1; st >= 0; --st) {
        int         big = 1 << st, fr = 0;
        vector<int> na(1 << st);
        for (int i = 1; i < 1 << st; i++) {
            int mn = min(arr2seed[2 * i], arr2seed[2 * i + 1]);
            int mx = max(arr2seed[2 * i], arr2seed[2 * i + 1]);
            if (mn == -1) {
                if (mx >= (1 << st)) {  // 有人赢了，但不知道是谁
                    --big;
                    na[i] = -1;
                } else if (mx != -1) {  // 知道是谁赢了，标记为mx
                    na[i] = mx;
                } else {  // 两个都是-1，那么可以*2
                    na[i] = -1;
                    ++fr;
                }
                continue;
            }
            if ((arr2seed[2 * i] < (1 << st)) == (arr2seed[2 * i + 1] < (1 << st))) {
                puts("0");
                return 0;
            }
            na[i] = mn;
            --big;
        }
        for (int _ = 0; _ < fr; _++) {
            ans = ans * 2ll % MOD;
        }
        for (int i = 1; i <= big; ++i) {
            ans = ans * 1ll * i % MOD;
        }
        arr2seed = na;
    }
    printf("%d\n", ans);
}