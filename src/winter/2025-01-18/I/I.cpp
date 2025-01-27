#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        vector<int> num_1(s.size() + 1);
        for (int i = 0; i < s.size(); i++)
        {
            num_1[i + 1] = s[i] - '0' + num_1[i];
        }
        int l = 0, r = s.size();
        int mid;
        while (l < r)
        {
            mid = (r - l) / 2 + l;
            int length = s.size() - mid;                                                                      // 新字符串长度
            if (length - num_1[length] >= num_1[s.size()] - mid && length - num_1[length] <= num_1[s.size()]) // 新字符串所需的1的数量 >= 1的数量至少为...
            {
                r = mid; // 满足了，可以少截点
            }
            else
            {
                l = mid + 1; // 不满足，多来点...
            }
        }
        cout << r << '\n';
    }
    return 0;
}