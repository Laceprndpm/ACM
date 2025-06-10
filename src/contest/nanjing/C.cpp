#include <bits/stdc++.h>
using namespace std;
typedef long long      ll;
typedef pair<int, int> pll;

void Tokisaki()
{
    int q, n;
    cin >> q >> n;
    vector<int> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        ans[i] = i;
    }
    // map<int, bool> mp;
    bool have_solve = 0;
    for (int i = 1; i <= q; i++) {
        int len;
        cin >> len;
        vector<int> a(len);
        for (int j = 0; j < len; j++)
            cin >> a[j];
        bool flag = 1;
        for (int j = 0; j < len; j++) {
            if (mp[a[j]]) {
                flag = 0;  // 不允许重排
                break;
            }
        }
        if (flag && i != 1) {
            swap(ans[i], ans[i - 1]);
            have_solve = 1;
            break;
        }
        mp.clear();
        for (int j = 0; j < len; j++)
            mp[a[j]] = 1;
    }
    if (have_solve) {
        cout << "Yes\n";
        for (int i = 1; i <= q; i++)
            cout << ans[i] << ' ';
        cout << '\n';
    } else
        cout << "No\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        Tokisaki();
    return 0;
}