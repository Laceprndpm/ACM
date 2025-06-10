#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int N = 100005;
constexpr int M = 100005;
constexpr int MOD = 10007;
int number[N];
int color[N];
LL color_eqmod_sum[M][2];
LL color_eqmod_cnt[M][2];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> number[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }
  for (int i = 1; i <= n; i++) {
    color_eqmod_sum[color[i]][i % 2] += number[i];
    color_eqmod_sum[color[i]][i % 2] %= MOD;
    color_eqmod_cnt[color[i]][i % 2]++;
  }
  LL ans = 0;
  for (LL i = 1; i <= n; i++) {
    ans += (color_eqmod_cnt[color[i]][i % 2] - 1) * i * number[i] +
           i * (color_eqmod_sum[color[i]][i % 2] - number[i]);
    ans %= MOD;
  }
  cout << (ans + MOD) % MOD << '\n';
  return 0;
}