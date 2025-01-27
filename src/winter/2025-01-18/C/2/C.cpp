#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int arr[N];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    unordered_map<int, int> num_v; // 记录每个元素出现的次数
    while (t--)
    {
        vector<int> num_k;
        int n, k;
        cin >> n >> k;
        num_v.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        for (int i = 0; i < n; i++)
        {
            num_v[arr[i]]++;
            if (num_v[arr[i]] == k)
            {
                num_k.emplace_back(arr[i]);
            }
        }
        sort(num_k.begin(), num_k.end());
        int l = 0, r = 0;
        int max_d = -1;
        int Ml = 0, Mr = 0;
        if (num_k.empty())
        {
            cout << -1 << '\n';
            continue;
        }
        while (r < num_k.size())
        {
            if (r - l == num_k[r] - num_k[l])
            {
                if (max_d < r - l)
                {
                    max_d = r - l;
                    Ml = num_k[l];
                    Mr = num_k[r];
                }
                r++;
            }
            else
            {
                l = r;
            }
        }
        cout << Ml << ' ' << Mr << '\n';
    }
    return 0;
}