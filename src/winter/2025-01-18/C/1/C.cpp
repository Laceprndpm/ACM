// #include <bits/stdc++.h>
// using namespace std;
// const int N = 2e5 + 5;
// int arr[N];
// inline int init()
// {
//     char c = getchar();
//     int x = 0, f = 1;
//     for (; c < '0' || c > '9'; c = getchar())
//         if (c == '-')
//             f = -1;
//     for (; c >= '0' && c <= '9'; c = getchar())
//         x = (x << 1) + (x << 3) + (c ^ 48);
//     return x * f;
// }
// inline void print(int x)
// {
//     if (x < 0)
//         x = -x, putchar('-');
//     if (x > 9)
//         print(x / 10);
//     putchar(x % 10 + '0');
// }

// signed main()
// {
//     ios::sync_with_stdio(false);
//     int t;
//     t = init();
//     unordered_map<int, int> num_v;
//     unordered_map<int, int> r2v;
//     set<int> types;
//     while (t--)
//     {
//         int n, k;
//         n = init();
//         k = init();
//         num_v.clear();
//         for (int i = 0; i < n; i++)
//         {
//             arr[i] = init();
//         }
//         types.clear();
//         for (int i = 0; i < n; i++)
//         {
//             num_v[arr[i]]++;
//             types.insert(arr[i]);
//         }
//         r2v.clear();
//         auto iter_set = types.begin();
//         for (int i = 0; i < types.size(); ++i)
//         {
//             r2v[i] = *(iter_set++); // 映射排名到值
//         }
//         int l = 0, r = 0;
//         int max_d = -1;
//         int Ml = 0, Mr = 0;
//         while (r < types.size())
//         {
//             if (num_v[r2v[r]] >= k)
//             {
//                 if (r2v[r] == (r2v[l] + (r - l)))
//                 {
//                     if ((r2v[r] - r2v[l]) > max_d)
//                     {
//                         max_d = r - l;
//                         Ml = r2v[l];
//                         Mr = r2v[r];
//                     }
//                     r++;
//                 }
//                 else
//                 {
//                     l = r;
//                 }
//             }
//             else
//             {
//                 l = ++r;
//             }
//         }

//         if (max_d == -1)
//         {
//             print(-1);
//             putchar('\n');
//         }
//         else
//         {
//             print(Ml);
//             putchar(' ');
//             print(Mr);
//             putchar('\n');
//         }
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        unordered_map<int, int> num_v;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        for (int i = 0; i < n; i++)
        {
            num_v[arr[i]]++;
        }

        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        std::unordered_map<int, int> r2v;
        for (int i = 0; i < (int)arr.size(); ++i)
        {
            r2v[i] = arr[i]; // 映射排名到值
        }
        int l = 0, r = 0;
        int max_d = -1;
        int Ml = 0, Mr = 0;
        while (r < (int)arr.size())
        {
            if (num_v[r2v[r]] >= k)
            {
                if (r2v[r] == (r2v[l] + (r - l)))
                {
                    if ((r2v[r] - r2v[l]) >= max_d)
                    {
                        max_d = r - l;
                        Ml = r2v[l];
                        Mr = r2v[r];
                    }
                    r++;
                }
                else
                {
                    l = r;
                }
            }
            else
            {
                l = ++r;
            }
        }
        if (max_d == -1)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << Ml << ' ' << Mr << '\n';
        }
    }
    return 0;
}

// 遍历数组，把出现次数大于k的数取出，加入到新数组，统计出现次数可以用map来存储