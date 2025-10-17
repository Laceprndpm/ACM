#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#define endl '\n'
#define ios  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
using namespace std;
typedef long long LL;

const int N = 5010;
LL        M;

vector<int>         primes;
int                 lp[N];
vector<vector<int>> vf;

void init()
{
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lp[i] || (LL)i * p > N) break;
            lp[i * p] = p;
        }
    }

    map<int, int> mp;
    for (int i = 0; i < primes.size(); ++i) {
        mp[primes[i]] = i;
    }

    vf.resize(primes.size(), vector<int>(N + 1, 0));

    for (int n = 2; n <= N; ++n) {
        int tt = n;
        while (tt > 1) {
            int p = lp[tt];
            vf[mp[p]][n]++;
            tt /= p;
        }
    }

    for (int i = 0; i < primes.size(); ++i) {
        for (int n = 2; n <= N; ++n) {
            vf[i][n] += vf[i][n - 1];
        }
    }
}

LL qmi(LL a, LL k)
{
    LL res = 1;
    while (k) {
        if (k & 1) res = (LL)res * a % M;
        a = (LL)a * a % M;
        k >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    map<int, int> cnts;
    LL            l = 0;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        l += c;
        cnts[c]++;
    }

    LL ans = 1;
    for (int i = 0; i < primes.size(); ++i) {
        int p = primes[i];
        if (p > l) break;

        LL res = vf[i][l];
        for (auto const &[val, num] : cnts) {
            res -= (LL)num * vf[i][val];
        }

        if (res > 0) {
            ans = (ans * qmi(p, res)) % M;
        }
    }
    cout << ans << endl;
}

signed main()
{
    ios;
    init();
    int T = 1;
    cin >> T >> M;
    while (T--) {
        solve();
    }
}