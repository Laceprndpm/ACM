#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

constexpr int MAXN = 5e6 + 5;
constexpr int TOTN = 5e6 + 5;

vector<LL>  num_factor(MAXN, 1);
vector<int> d_x(MAXN);
vector<int> d_y(MAXN);

void initCnt()
{
    for (LL i = 2; i <= (int)5e6; i++) {
        if (num_factor[i] == 1) {
            for (LL j = 2; j * i <= (int)5e6; j++) {
                num_factor[i * j] = num_factor[j] + num_factor[i];
            }
        }
    }
    num_factor[1] = 0;
    num_factor[0] = -1;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initCnt();
    int M, N, X, Y;
    cin >> M >> N >> X >> Y;
    for (int i = 0; i <= X; i++) {
        d_x[num_factor[M - i]]++;
    }
    for (int j = 0; j <= Y; j++) {
        d_y[num_factor[N - j]]++;
    }
    LL ans = 0;
    for (int i = 0; i <= max(N, M); i++) {
        ans += d_x[i] * (LL)d_y[i];
    }
    cout << (X + 1) * (LL)(Y + 1) - ans;
    return 0;
}