#ifdef V1
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int M = 2e3 + 5;
constexpr int N = 1e6 + 5;
int input[N];
int num_place[M];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> input[i];
    }
    int l = 0, r = 0;
    int R, L;
    int total_num = 0;
    int min_d = INT32_MAX;
    while (r < n && total_num < m)
    {
        ++r;
        if (++num_place[input[r]] == 1)
        {
            ++total_num;
        }
    }
    R = r;
    L = l;
    min_d = R - L;
    do
    {
        while (l < n && total_num == m)
        {
            if (--num_place[input[++l]] == 0)
            {
                if (r - l < min_d)
                {
                    min_d = r - l;
                    R = r;
                    L = l;
                }
                --total_num;
            }
        }
        while (r < n && total_num < m)
        {
            ++r;
            if (++num_place[input[r]] == 1)
            {
                ++total_num;
            }
        }
    } while (r < n);
    cout << L << ' ' << R << '\n';
    return 0;
}
#endif

#ifdef V2
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int M = 2e3 + 5;
constexpr int N = 1e6 + 5;
int input[N];
int num_place[M]; // 区间内，i画家画的数量为v
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> input[i];
    }
    int l = 0, r = 0;
    int R, L;
    int total_num = 0;
    int min_d = INT32_MAX;
    input[n + 1] = 0;
    num_place[0] = 5;
    while (r <= n)
    {
        if (total_num < m)
        {
            r++;
            num_place[input[r]]++;
            if (num_place[input[r]] == 1)
                total_num++;
        }
        else
        {
            if (min_d > r - l)
            {
                min_d = r - l;
                R = r;
                L = l;
            }
            l++;
            num_place[input[l - 1]]--;
            if (num_place[input[l - 1]] == 0)
                total_num--;
        }
    }
    cout << L << ' ' << R << '\n';
    return 0;
}
#endif

#ifdef V3
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int M = 2e3 + 5;
constexpr int N = 1e6 + 5;
int input[N];
int num_place[M];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> input[i];
    }
    int l = 0, r = 0;
    int R, L;
    int total_num = 0;
    int min_d = INT32_MAX;
    input[n + 1] = 0;
    num_place[0] = 5;
    while (r < n)
    {
        if (total_num < m)
        {
            r++;
            num_place[input[r]]++;
            if (num_place[input[r]] == 1)
                total_num++;
        }
        else
        {
            if (min_d > r - l - 1)
            {
                min_d = r - l - 1;
                R = r;
                L = l + 1;
            }
            l++;
            num_place[input[l]]--;
            if (num_place[input[l]] == 0)
                total_num--;
        }
    }
    while (total_num == m)
    {
        if (min_d > r - l - 1)
        {
            min_d = r - l - 1;
            R = r;
            L = l + 1;
        }
        l++;
        num_place[input[l]]--;
        if (num_place[input[l]] == 0)
            total_num--;
    }
    cout << L << ' ' << R << '\n';
    return 0;
}
#endif