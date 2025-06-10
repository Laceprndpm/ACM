// #include <bits/stdc++.h>
// using namespace std;
// using i64 = long long;
// using PII = pair<int, int>;
// string                 s;
// int                    m;
// string                 l, r;
// int                    n;
// vector<array<int, 10>> vec;

// bool DFS(int substringidx, int stringidx)
// // 已经匹配了substringidx前面所有字符，并且在stringidx处
// {
//     if (substringidx == m) {
//         return false;
//     }
//     bool hasans = false;

//     for (char i = l[substringidx]; i <= r[substringidx]; i++) {
//         if (vec[stringidx][i - '0'] == -1) {
//             return true;
//         } else {
//             hasans |= DFS(substringidx + 1, vec[stringidx][i - '0']);
//         }
//     }

//     return hasans;
// }

// void solve()
// {
//     cin >> s;
//     cin >> m;
//     cin >> l >> r;
//     s = "-" + s;
//     n = s.size();
//     array<int, 10> last;
//     vec.resize(n + 1);
//     for (int i = 0; i < 10; i++) {
//         last[i] = -1;
//     }

//     for (int i = n - 1; i >= 0; i--) {
//         for (int j = 0; j <= 9; j++) {
//             vec[i][j] = last[j];
//         }
//         if (i != 0) last[s[i] - '0'] = i;
//     }

//     if (DFS(0, 0)) {
//         cout << "YES\n";
//     } else {
//         cout << "NO\n";
//     }
// }

// signed main(int argc, char** argv)
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
using i64          = long long;
using PII          = pair<int, int>;
constexpr int maxn = 15;
int           T, m;
int           cnt[maxn];
bool          vis[maxn][10];
string        s, l, r;

bool check()
{
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        if (cnt[j] == r[j] - l[j] + 1) {
            j++;
        }
        if (j > m - 1) {
            return 0;
        }
        if (s[i] >= l[j] && s[i] <= r[j] && !vis[j][s[i] - '0']) {
            vis[j][s[i] - '0'] = 1, cnt[j]++;
        }
    }
    return (j < m - 1 || (j == m - 1 && cnt[j] != r[j] - l[j] + 1));
}

void solve()
{
    cin >> s;
    cin >> m;
    cin >> l >> r;
    if (check()) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }
}

int main()
{
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}