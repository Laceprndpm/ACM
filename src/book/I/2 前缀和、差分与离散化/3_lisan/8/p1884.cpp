#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int           n;
int           rectangle[4004][4];
int           val2rank[4050];
int           f[4050][4050];
int           val2ranktop = 1;
map<int, int> rank2val;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 3; j++) {
            cin >> rectangle[i][j];
        }
    }

    {
        vector<int> discrete((int*)(rectangle[1]), (int*)(rectangle[n + 1]));
        sort(discrete.begin(), discrete.end());

        val2rank[val2ranktop] = discrete[0];
        rank2val[discrete[0]] = val2ranktop;

        for (int i = 1; i < discrete.size(); i++) {
            if (discrete[i] != discrete[i - 1]) {
                val2rank[++val2ranktop] = discrete[i];
                rank2val[discrete[i]]   = val2ranktop;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 3; j++) {
            rectangle[i][j] = rank2val[rectangle[i][j]];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = rectangle[i][0]; j < rectangle[i][2]; j++) {
            f[j][rectangle[i][1]]--, f[j][rectangle[i][3]]++;
        }
    }

    for (int i = 1; i < val2ranktop; i++) {
        for (int j = 1; j < val2ranktop; j++) {
            f[i][j] += f[i][j - 1];
        }
    }

    LL ans = 0;
    for (int i = 1; i < val2ranktop; i++) {
        for (int j = 1; j < val2ranktop; j++) {
            if (f[i][j]) {
                ans += (LL)(val2rank[i + 1] - val2rank[i]) * (val2rank[j + 1] - val2rank[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}

// #include "bits/stdc++.h"
// using namespace std;
// #define MAXN 4010
// int           n, btop, ctop;
// int           a[MAXN][4];
// int           b[MAXN * 4], c[MAXN * 4];
// int           f[MAXN][MAXN];
// map<int, int> mp;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
//     cin >> n;
//     for (int i = 1; i <= n; i++) {
//         for (int j = 0; j < 4; j++) {
//             cin >> a[i][j];
//             b[++btop] = a[i][j];
//         }
//     }
//     sort(b + 1, b + btop + 1);
//     b[0] = -1e9 - 7;
//     for (int i = 1; i <= btop; i++) {
//         if (b[i] != b[i - 1]) {
//             c[++ctop] = b[i];
//             mp[b[i]]  = ctop;
//         }
//     }
//     for (int i = 1; i <= n; i++) {
//         for (int j = 0; j < 4; j++) {
//             a[i][j] = mp[a[i][j]];
//         }
//     }
//     // 进行矩形覆盖
//     for (int k = 1; k <= n; k++) {
//         for (int i = a[k][0]; i < a[k][2]; i++) {
//             f[i][a[k][3]]++, f[i][a[k][1]]--;
//         }
//     }
//     for (int i = 1; i < ctop; i++) {
//         for (int j = 1; j < ctop; j++) {
//             f[i][j] += f[i][j - 1];
//         }
//     }
//     long long ans = 0;
//     for (int i = 1; i < ctop; i++) {
//         for (int j = 1; j < ctop; j++) {
//             if (f[i][j] > 0) {
//                 ans += (long long)(c[i + 1] - c[i]) * (c[j + 1] - c[j]);
//             }
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }