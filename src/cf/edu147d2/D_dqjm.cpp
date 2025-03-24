#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> lx(n), rx(n);
        for (int i = 0; i <= n - 1; i++) {
            cin >> lx[i];
        }
        for (int i = 0; i <= n - 1; i++) {
            cin >> rx[i];
        }
        int cnt = 0;
        int sum = 0, ans = 2e9;
        for (int i = 0; i <= n - 1; i++) {
            int len = rx[i] - lx[i] + 1;
            if (len == 1) {
                cnt++;
            }
            sum += len;
            if (sum >= m) {
                int remain = sum - m;  // 多余的染色
                int res    = rx[i] - remain + 2 * (i + 1) - min(remain, cnt);
                // 先剔除remain，即多染色的部分，随后开始将cnt补到remain的部分
                // min(remain, cnt)为将那些len == 1的地方剔除
                ans = min(ans, res);
                // 总结：
            }
        }
        if (ans == 2e9)
            cout << -1 << endl;
        else
            cout << ans << endl;
    }
    return 0;
}

// 若你打碎天上的双月，寒夜中的人无可仰望，唯有闭上双眼，光明终成为幻想与骗局。你果真相信那样的永夜更有良心？