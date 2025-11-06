#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define fi first
#define se second
#define pb push_back
void solve()
{
    string s;
    cin >> s;
    // 用队列模拟两次可以吗？
    // 如果空就不pop，否则必然pop
    // 则会怎么样？
    // 2222222220101010010
    // 不存在2前面有其他数字
    // 01022010
    // 这样是不是错了？
    // 0010->10
    // 但是标准做法是22拼接，然后就可以010010 = 0
    //
    //
    // minimum
    // 二分？
    // 贪心？假如先让被2分割的块优先匹配，绝不会让答案更劣
    // 后续怎么考虑不同快间复合？
    // 每个2是不是必须选前者或者后者进行匹配？
    // dp？
    // 状态空间可以压缩吗？
    // 怎么感觉有点像马拉车，把所有回文的找到，然后就可以dp，dp[i]表示第i位，最多保留多少无法删除的
    //
    //
    int n = s.length();
    string t = "-#";
    for (int i = 0; i < n; i++)
    {
        t += s[i];
        t += '#';
    }
    int m = t.length();
    t += '+';
    int mid = 0, r = 0;
    vector<int> p(m);
    auto equal = [](char a, char b)
    {
        if (a == '-' || a == '+' || b == '-' || b == '+')
            return false;
        if (a == '2' || b == '2')
            return true;
        else
            return a == b;
    };

    for (int i = 1; i < m; i++)
    {
        p[i] = i < r ? min(p[2 * mid - i], r - i) : 1;
        while (equal(t[i - p[i]], t[i + p[i]]))
            p[i]++;
        if (i + p[i] > r)
        {
            r = i + p[i];
            mid = i;
        }
    }
    vector<int> dp(m + 1, 1e9);
    dp[0] = 0;
    for (int i = 1; i < m - 1; i++)
    {
        if (t[i] == '#')
        {
            dp[i] = min(dp[i], dp[i - 1]);
            int maxskip = min({p[i], m - i - 1, i - 1});
            dp[maxskip + i - 1] = min(dp[maxskip + i - 1], dp[i - maxskip]);
        }
        else
        {
            dp[i] = min(dp[i], dp[i - 1] + 1);
        }
    }
    cout << (dp[m - 2]) << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}