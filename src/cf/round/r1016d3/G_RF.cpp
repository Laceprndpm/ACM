#include <bits/stdc++.h>
using namespace std;

const int         maxn = 2e6 + 5;
int               a[maxn], b[maxn];
typedef long long ll;

int n, k;
int mn;

void solve()
{

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = 0;
    if (k == 0) {
        cout << "1" << endl;
        return;
    }
    int limit = 0;  // 只有两个异或和等于limit的元素才可以组成一对
    // b[i]: 第i个数字的标记数组
    mn = n + 1;
    for (int j = 30; j >= 0; j--) {
        // 第j位为1，此时选择的两个数字必须一个为0，一个为1
        //        cout << j << endl;
        if (k & (1 << j)) {
            limit |= 1 << j;
            for (int i = 1; i <= n; i++) {
                if (a[i] & (1 << j)) b[i] |= 1 << j;
            }
        } else {
            // 第j位为0时，若本位为1直接符合条件，记录答案至min
            // 其余情况继续
            map<int, int> mp[2];  // [key:value]: 上一个b值为key的位置为value
            // mp[0]: 当前位为0，mp[1]: 当前位为1
            for (int i = 1; i <= n; i++) {
                bool flag = (a[i] & (1 << j)) > 0;
                if (mp[!flag].count(limit ^ b[i])) {
                    mn = min(mn, i - mp[!flag][limit ^ b[i]] + 1);
                }
                mp[flag][b[i]] = i;
            }
        }
    }

    // 最后，查询所有满足条件的元素的情况的答案
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        if (mp.count(limit ^ b[i])) mn = min(mn, i - mp[limit ^ b[i]] + 1);
        mp[b[i]] = i;
    }
    if (mn != n + 1)
        cout << mn << endl;
    else
        cout << -1 << endl;
}

int main()
{

    int t;
    cin >> t;
    while (t--)
        solve();
}
