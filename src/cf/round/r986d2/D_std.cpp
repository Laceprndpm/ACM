#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using pii = pair<int, int>;
using vi  = vector<int>;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x)       (x).begin(), (x).end()
#define sz(x)        (int)(x).size()
#define smx(a, b)    a = max(a, b)
#define smn(a, b)    a = min(a, b)
#define pb           push_back
#define endl         '\n'

const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;

mt19937 rng(time(0));

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    std::string s = "qkj";
    while (t--) {
        int n;
        cin >> n;
        vector p(3, vector<int>(n + 1));
        rep(i, 0, 3) rep(j, 1, n + 1) cin >> p[i][j];
        vector<pair<char, int>> sol(n + 1, {'\0', -1});
        array<int, 3>           mins = {n, n, n};  // minimizing index
        for (int i = n - 1; i >= 1; i--) {
            int win                                       = -1;
            rep(j, 0, 3) if (p[j][i] > p[j][mins[j]]) win = j;
            if (win == -1) continue;
            sol[i]                                            = {s[win], mins[win]};
            rep(j, 0, 3) if (p[j][i] < p[j][mins[j]]) mins[j] = i;
        }
        if (sol[1].second == -1) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        vector<pair<char, int>> ans = {sol[1]};
        while (ans.back().second >= 0) {
            ans.push_back(sol[ans.back().second]);
        }
        ans.pop_back();
        cout << sz(ans) << "\n";
        for (auto&& [c, i] : ans) {
            cout << c << " " << i << "\n";
        }
    }
}