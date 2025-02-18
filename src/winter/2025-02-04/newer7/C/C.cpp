#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 1e6 + 50;

int  mu[MAXN];
bool flg[MAXN];
int  p[MAXN];
int  tot = 0;
int  cnt_input_k[MAXN];
int  cnt_b_minus1[MAXN];
int  cnt_factor_b_minus1[MAXN];
int  cnt_factor_k[MAXN];

void getMu(int n = 1e6)
{
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!flg[i])
            p[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * p[j] <= n; ++j) {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0) {
                mu[i * p[j]] = 0;
                break;
            }
            mu[i * p[j]] = -mu[i];
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    getMu();
    int length_k, length_b;
    cin >> length_k >> length_b;
    for (int i = 1; i <= length_k; i++) {
        int temp;
        cin >> temp;
        cnt_input_k[temp]++;
    }
    for (int i = 1; i <= length_b; i++) {
        int temp;
        cin >> temp;
        cnt_b_minus1[temp - 1]++;
    }

    for (int div = 1; div <= (int)1e6; ++div) {
        for (int k = 1; k * div <= (int)1e6; ++k) {
            cnt_factor_k[div] += cnt_input_k[k * div], cnt_factor_b_minus1[div] += cnt_b_minus1[k * div];
        }
    }
    LL ans = 0;
    for (int d = 1; d <= (int)1e6; d++) {
        ans += mu[d] * (LL)cnt_factor_k[d] * cnt_factor_b_minus1[d];
    }
    cout << ans;
    return 0;
}