#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int k = 4;
    int n = 8;
    int ans = 0;
    for (int i = 0; i < (1 << n); i += 2)
    {
        int and_sum = 11;
        int XOR_sum = 0;
        for (int j = 0; j < k; j++)
        {
            and_sum &= ((i >> j * 2) & 3);
            XOR_sum ^= ((i >> j * 2) & 3);
        }
        if (and_sum >= XOR_sum)
        {
            ans++;
        }
    }
    cout << ans;
}
// k = 1
//  n   ans
//  0   1
//  1   2   - 1
//  2   2
//  3   5   - 4
//  4   8
//  5   17  - 16
//  6   32
//  7   65  - 64
//  8   128

// k = 2
//  n   ans
//  2   3
//  3   10
//  4   36